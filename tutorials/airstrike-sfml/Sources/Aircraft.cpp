
#include "Aircraft.hpp"
#include "DataTables.hpp"
#include "Utility.hpp"
#include "Pickup.hpp"
#include "CommandQueue.hpp"
#include "SoundNode.hpp"
#include "NetworkNode.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>


using namespace std::placeholders; // TODO: get rid of this

namespace {
const std::vector<AircraftData> Table = initalizeAircraftData();
} // namespace


Aircraft::Aircraft( Type type, const TextureHolder& textures, const FontHolder& fonts ) :
Entity( Table[type].hitpoints ),
mType( type ),
mSprite( textures.get( Table[type].texture ), Table[type].textureRect ),
mExplosion( textures.get( Textures::Explosion ) ),
mFireCommand(),
mMissileCommand(),
mFireCountdown( sf::Time::Zero ),
mIsFiring( false ),
mIsLaunchingMissile( false ),
mShowExplosion( true ),
mExplosionBegan( false ),
mSpawnedPickup( false ),
mPickupsEnabled( true ),
mFireRateLevel( 1 ),
mSpreadLevel( 1 ),
mMissileAmmo( 2 ),
mDropPickupCommand(),
mTravelledDistance( 0.0f ),
mDirectionIndex( 0 ),
mHealthDisplay( nullptr ),
mMissileDisplay( nullptr ),
mIdentifier( 0 ) {

    mExplosion.setFrameSize( sf::Vector2i( 256, 256 ) );
    mExplosion.setNumFrames( 16 );
    mExplosion.setDuration( sf::seconds( 1 ) );

    centerOrigin( mSprite );
    centerOrigin( mExplosion );

    mFireCommand.category        = Category::SceneAirLayer;
    mFireCommand.action          = [ this, &textures ] ( SceneNode& node, sf::Time ) {
        createBullets( node, textures );
    };

    mMissileCommand.category    = Category::SceneAirLayer;
    mMissileCommand.action      = [ this, &textures ] ( SceneNode& node, sf::Time ) {
        createProjectile( node, Projectile::Missile, 0.0f, 0.5f, textures );
    };

    mDropPickupCommand.category = Category::SceneAirLayer;
    mDropPickupCommand.action   = [ this, &textures ] ( SceneNode& node, sf::Time ) {
        createPickup( node, textures );
    };

    std::unique_ptr<TextNode> healthDisplay( new TextNode( fonts, "" ) );
    mHealthDisplay              = healthDisplay.get();
    attachChild( std::move( healthDisplay ) );

    if ( getCategory() == Category::PlayerAircraft ) {
        std::unique_ptr<TextNode> missileDisplay( new TextNode( fonts, "" ) );
        missileDisplay->setPosition( 0, 70 );
        mMissileDisplay = missileDisplay.get();
        attachChild( std::move( missileDisplay ) );
    }
    updateTexts();
}

int
Aircraft::getMissileAmmo() const {
    return mMissileAmmo;
}

void
Aircraft::setMissileAmmo( int ammo ) {
    mMissileAmmo = ammo;
}

void
Aircraft::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const {
    if ( isDestroyed() && mShowExplosion ) {
        target.draw( mExplosion, states );
    } else {
        target.draw( mSprite, states );
    }
}

void
Aircraft::disablePickups() {
    mPickupsEnabled = false;
}

void
Aircraft::updateCurrent( sf::Time dt, CommandQueue& commands ) {
    updateTexts();
    updateRollAnimation();

    // Entity has been destroyed: Possibly drop pickup, mark for removal
    if ( isDestroyed() ) {
        checkPickupDrop( commands );
        mExplosion.update( dt );

        // Play explosion sound only once
        if ( !mExplosionBegan ) {
            // Play sound effect
            // TODO: put it into function
            SoundEffect::ID soundEffect = ( randomInt( 2 ) == 0 ) ? SoundEffect::Explosion1 : SoundEffect::Explosion2;
            playLocalSound( commands, soundEffect );

            // Emit network gme action for enemy explosions
            if ( !isAllied() ) {
                sf::Vector2f position = getWorldPosition();

                Command command;
                command.category = Category::Network;
                command.action      = derivedAction<NetworkNode>(
                    [position] ( NetworkNode& node, sf::Time ) {
                        node.notifyGameAction( GameActions::EnemyExplode, position );
                    }
                );
                commands.push( command );
            }
            mExplosionBegan = true;
        }
        return;
    }

    checkProjectileLaunch( dt, commands );

    updateMovementPattern( dt );
    Entity::updateCurrent( dt, commands );
}

unsigned int
Aircraft::getCategory() const {
    if ( isAllied() ) {
        return Category::PlayerAircraft;
    } else {
        return Category::EnemyAircraft;
    }
}

sf::FloatRect
Aircraft::getBoundingRect() const {
    return getWorldTransform().transformRect( mSprite.getGlobalBounds() );
}

bool 
Aircraft::isMarkedForRemoval() const {
    return isDestroyed() && ( mExplosion.isFinished() || !mShowExplosion );
}

void
Aircraft::remove() {
    Entity::remove();
    mShowExplosion = false;
}

bool
Aircraft::isAllied() const {
    return mType == Eagle;
}

float
Aircraft::getMaxSpeed() const {
    return Table[mType].speed;
}

void
Aircraft::increaseFireRate() {
    if ( mFireRateLevel < 10 ) {
        mFireRateLevel++;
    }
}

void
Aircraft::increaseSpread() {
    if ( mSpreadLevel < 3 ) {
        mSpreadLevel++;
    }
}

void
Aircraft::collectMissiles( unsigned int count ) {
    mMissileAmmo += count;
}

void
Aircraft::fire() {
    // Only ships with fire interval != 0 ate able to fire
    if ( Table[mType].fireInterval != sf::Time::Zero ) {
        mIsFiring = true;
    }
}

void
Aircraft::launchMissile() {
    if ( mMissileAmmo > 0 ) {
        mIsLaunchingMissile = true;
        mMissileAmmo--;
    }
}

void
Aircraft::playLocalSound( CommandQueue& commands, SoundEffect::ID effect ) {
    sf::Vector2f worldPosition = getWorldPosition();

    Command command;
    command.category    = Category::SoundEffect;
    command.action      = derivedAction<SoundNode>(
        [effect, worldPosition] ( SoundNode& node, sf::Time ) {
            node.playSound( effect, worldPosition );
        }
    );
    commands.push( command );
}

int
Aircraft::getIdentifier() {
    return mIdentifier;
}

void
Aircraft::setIdentifier( int identifier ) {
    mIdentifier = identifier;
}

void
Aircraft::updateMovementPattern( sf::Time dt ) {
    // Enemy Airplane: Movement pattern
    const std::vector<Direction>& directions = Table[mType].directions;
    if ( !directions.empty() ) {
        // Moved long enough in current direction: change direction
        // TODO: Wrap condition into function
        if ( mTravelledDistance > directions[mDirectionIndex].distance ) { 
            mDirectionIndex     = ( mDirectionIndex + 1 ) % directions.size();
            mTravelledDistance  = 0.0f;
        }

        // Compute velocity from direction
        float radians   = toRadian( directions[mDirectionIndex].angle + 90.0f );
        float vx        = getMaxSpeed() * std::cos( radians );
        float vy        = getMaxSpeed() * std::sin( radians );

        setVelocity( vx, vy );

        mTravelledDistance += getMaxSpeed() * dt.asSeconds();
    }
}

void
Aircraft::checkPickupDrop( CommandQueue& commands ) {
    // TODO: Wrap condition into function
    if ( !isAllied() && randomInt( 3 ) == 0 && !mSpawnedPickup && mPickupsEnabled ) {
        commands.push( mDropPickupCommand );
    }
    mSpawnedPickup = true;
}

void
Aircraft::checkProjectileLaunch( sf::Time dt, CommandQueue& commands ) {
    // Enemies try to fire all the time
    if ( !isAllied() ) {
        fire();
    }

    // Check for automatic gunfire, allow only in intervals
    if ( mIsFiring && mFireCountdown <= sf::Time::Zero ) {
        commands.push( mFireCommand );
        playLocalSound( commands, isAllied() ? SoundEffect::AlliedGunfire : SoundEffect::EnemyGunfire );

        mFireCountdown += Table[mType].fireInterval / ( mFireRateLevel + 1.0f );
        mIsFiring = false;
    } else if ( mFireCountdown > sf::Time::Zero ) {
        mFireCountdown -= dt;
        mIsFiring = false;
    }

    if ( mIsLaunchingMissile ) {
        commands.push( mMissileCommand );
        playLocalSound( commands, SoundEffect::LaunchMissile );
        mIsLaunchingMissile = false;
    }
}

void
Aircraft::createBullets( SceneNode& node, const TextureHolder& textures ) const {
    // TODO: put this shit into function
    Projectile::Type type = isAllied() ? Projectile::AlliedBullet : Projectile::EnemyBullet;

    switch ( mSpreadLevel ) {
        case 1:
            createProjectile( node, type, 0.0f, 0.5f, textures );
            break;
        case 2:
            createProjectile( node, type, -0.33f, 0.33f, textures );
            createProjectile( node, type, +0.33f, 0.33f, textures );
            break;
        case 3:
            createProjectile( node, type, -0.5f, 0.33f, textures );
            createProjectile( node, type, 0.0f, 0.5f, textures );
            createProjectile( node, type, +0.5f, 0.33f, textures );
            break;
    }
}

void
Aircraft::createProjectile(
    SceneNode& node,
    Projectile::Type type,
    float xOffset,
    float yOffset,
    const TextureHolder& textures
) const {
    std::unique_ptr<Projectile> projectile( new Projectile( type, textures ) );

    sf::Vector2f offset(
        xOffset * mSprite.getGlobalBounds().width, 
        yOffset * mSprite.getGlobalBounds().height
    );
    sf::Vector2f velocity( 0, projectile->getMaxSpeed() );

    float sign = isAllied() ? -1.0f : +1.0f; // Die!!!
    projectile->setPosition( getWorldPosition() + offset * sign );
    projectile->setVelocity( velocity * sign );
    node.attachChild( std::move( projectile ) );
}

void
Aircraft::createPickup( SceneNode& node, const TextureHolder& textures ) const {
    auto type = static_cast<Pickup::Type>( randomInt( Pickup::TypeCount ) );

    std::unique_ptr<Pickup> pickup( new Pickup( type, textures ) );
    pickup->setPosition( getWorldPosition() );
    pickup->setVelocity( 0.0f, 1.0f );
    node.attachChild( std::move( pickup ) );
}

void
Aircraft::updateTexts() {
    if ( isDestroyed() ) {
        mHealthDisplay->setString( "" );
    } else {
        mHealthDisplay->setString( std::to_string( getHitpoints() ) + " HP" );
    }
    mHealthDisplay->setPosition( 0.0f, 50.0f );
    mHealthDisplay->setRotation( -getRotation() );

    if ( mMissileDisplay ) {
        if ( mMissileAmmo == 0 || isDestroyed() ) {
            mMissileDisplay->setString( "" );
        } else {
            mMissileDisplay->setString( "M: " + std::to_string( mMissileAmmo ) );
        }
    }
}

void
Aircraft::updateRollAnimation() {
    if ( Table[mType].hasRollAnimation ) {
        sf::IntRect textureRect = Table[mType].textureRect;

        if ( getVelocity().x < 0.0f ) {
            textureRect.left += textureRect.width;
        } else if ( getVelocity().x > 0.0f ) {
            textureRect.left += 2 * textureRect.width;
        }
        mSprite.setTextureRect( textureRect );
    }
}
