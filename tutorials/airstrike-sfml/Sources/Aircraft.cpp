
#include "Aircraft.hpp"


using namespace std::placeholders;

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
        CreateBullets( node, textures );
    };

    mMissileCommand.category    = Category::SceneAirLayer;
    mMissileCommand.action      = [ this, &textures ] ( SceneNode& node, sf::Time ) {
        CreateProjectile( node, Projectile::Missile, 0.0f, 0.5f, textures );
    };

    mDropPickupCommand.category = Category::SceneAirLayer;
    mDropPickupCommand.action   = [ this, &textures ] ( SceneNode& node, sf::Time ) {
        CreatePickup( node, textures );
    };

    std::unique_ptr<TextNode> healthDisplay( new TextNode( fonts, "" ) );
    mHealthDisplay              = healthDisplay.get();
    AttachChild( std::move( healthDisplay ) );

    if ( GetCategory() == Category::PlayerAircraft ) {
        std::unique_ptr<TextNode> missileDisplay( new TextNode( fonts, "" ) );
        missileDisplay->setPosition( 0, 70 );
        mMissileDisplay = missileDisplay.get();
        AttachChild( std::move( missileDisplay ) );
    }
    UpdateTexts();
}

int
Aircraft::GetMissileAmmo() const {
    return mMissileAmmo;
}

void
Aircraft::SetMissileAmmo( int ammo ) {
    mMissileAmmo = ammo;
}

void
Aircraft::DrawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const {
    if ( IsDestroyed() && mShowExplosion ) {
        target.draw( mExplosion, states );
    } else {
        target.draw( mSprite, states );
    }
}

void
Aircraft::DisablePickups() {
    mPickupsEnabled = false;
}

void
Aircraft::UpdateCurrent( sf::Time dt, CommandQueue& commands ) {
    UpdateTexts();
    UpdateRollAnimation();

    // Entity has been destroyed: Possibly drop pickup, mark for removal
    if ( IsDestroyed() ) {
        CheckPickupDrop( commands );
        mExplosion.update( dt );

        // Play explosion sound only once
        if ( !mExplosionBegan ) {
            // Play sound effect
            SoundEffect::ID soundEffect = this->GetRandomExplosionSound();
            PlayLocalSound( commands, soundEffect );

            // Emit network gme action for enemy explosions
            if ( !IsAllied() ) {
                sf::Vector2f position = GetWorldPosition();

                Command command;
                command.category    = Category::Network;
                command.action      = derivedAction<NetworkNode>(
                    [position] ( NetworkNode& node, sf::Time ) {
                        node.NotifyGameAction( GameActions::EnemyExplode, position );
                    }
                );
                commands.push( command );
            }
            mExplosionBegan = true;
        }
        return;
    }

    CheckProjectileLaunch( dt, commands );

    UpdateMovementPattern( dt );
    Entity::UpdateCurrent( dt, commands );
}

unsigned int
Aircraft::GetCategory() const {
    if ( IsAllied() ) {
        return Category::PlayerAircraft;
    } else {
        return Category::EnemyAircraft;
    }
}

sf::FloatRect
Aircraft::GetBoundingRect() const {
    return GetWorldTransform().transformRect( mSprite.getGlobalBounds() );
}

bool 
Aircraft::IsMarkedForRemoval() const {
    return IsDestroyed() && ( mExplosion.isFinished() || !mShowExplosion );
}

void
Aircraft::Remove() {
    Entity::Remove();
    mShowExplosion = false;
}

bool
Aircraft::IsAllied() const {
    return mType == Eagle;
}

float
Aircraft::GetMaxSpeed() const {
    return Table[mType].speed;
}

void
Aircraft::IncreaseFireRate() {
    if ( mFireRateLevel < 10 ) {
        mFireRateLevel++;
    }
}

void
Aircraft::IncreaseSpread() {
    if ( mSpreadLevel < 3 ) {
        mSpreadLevel++;
    }
}

void
Aircraft::CollectMissiles( unsigned int count ) {
    mMissileAmmo += count;
}

void
Aircraft::Fire() {
    // Only ships with fire interval != 0 ate able to fire
    if ( Table[mType].fireInterval != sf::Time::Zero ) {
        mIsFiring = true;
    }
}

void
Aircraft::LaunchMissile() {
    if ( mMissileAmmo > 0 ) {
        mIsLaunchingMissile = true;
        mMissileAmmo--;
    }
}

void
Aircraft::PlayLocalSound( CommandQueue& commands, SoundEffect::ID effect ) {
    sf::Vector2f worldPosition = GetWorldPosition();

    Command command;
    command.category    = Category::SoundEffect;
    command.action      = derivedAction<SoundNode>(
        [effect, worldPosition] ( SoundNode& node, sf::Time ) {
            node.playSound( effect );
        }
    );
    commands.push( command );
}

int
Aircraft::GetIdentifier() const {
    return mIdentifier;
}

void
Aircraft::SetIdentifier( int identifier ) {
    mIdentifier = identifier;
}

void
Aircraft::UpdateMovementPattern( sf::Time dt ) {
    // Enemy Airplane: Movement pattern
    const std::vector<Direction>& directions = Table[mType].directions;
    if ( !directions.empty() ) {
        // Moved long enough in current direction: change direction
        if ( mTravelledDistance > directions[mDirectionIndex].distance ) { 
            mDirectionIndex     = ( mDirectionIndex + 1 ) % directions.size();
            mTravelledDistance  = 0.0f;
        }

        // Compute velocity from direction
        float radians   = toRadian( directions[mDirectionIndex].angle + 90.0f );
        float vx        = GetMaxSpeed() * std::cos( radians );
        float vy        = GetMaxSpeed() * std::sin( radians );

        SetVelocity( vx, vy );

        mTravelledDistance += GetMaxSpeed() * dt.asSeconds();
    }
}

void
Aircraft::CheckPickupDrop( CommandQueue& commands ) {
    if ( this->PickupDropCondition() ) {
        commands.push( mDropPickupCommand );
    }
    mSpawnedPickup = true;
}

void
Aircraft::CheckProjectileLaunch( sf::Time dt, CommandQueue& commands ) {
    // Enemies try to fire all the time
    if ( !IsAllied() ) {
        Fire();
    }

    // Check for automatic gunfire, allow only in intervals
    if ( mIsFiring && mFireCountdown <= sf::Time::Zero ) {
        commands.push( mFireCommand );
        this->PlayLocalSound( commands, this->GetGunfireSoundId() );

        mFireCountdown += Table[mType].fireInterval / ( mFireRateLevel + 1.0f );
        mIsFiring = false;
    } else if ( mFireCountdown > sf::Time::Zero ) {
        mFireCountdown -= dt;
        mIsFiring = false;
    }

    if ( mIsLaunchingMissile ) {
        commands.push( mMissileCommand );
        PlayLocalSound( commands, SoundEffect::LaunchMissile );
        mIsLaunchingMissile = false;
    }
}

void
Aircraft::CreateBullets( SceneNode& node, const TextureHolder& textures ) const {
    Projectile::Type type = this->GetBulletType();
    switch ( mSpreadLevel ) {
        case 1:
            CreateProjectile( node, type, 0.0f, 0.5f, textures );
            break;
        case 2:
            CreateProjectile( node, type, -0.33f, 0.33f, textures );
            CreateProjectile( node, type, +0.33f, 0.33f, textures );
            break;
        case 3:
            CreateProjectile( node, type, -0.5f, 0.33f, textures );
            CreateProjectile( node, type, 0.0f, 0.5f, textures );
            CreateProjectile( node, type, +0.5f, 0.33f, textures );
            break;
    }
}

void
Aircraft::CreateProjectile(
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
    sf::Vector2f velocity( 0, projectile->GetMaxSpeed() );

    float sign = this->GetBulletSign();
    projectile->setPosition( GetWorldPosition() + offset * sign );
    projectile->SetVelocity( velocity * sign );
    node.AttachChild( std::move( projectile ) );
}

void
Aircraft::CreatePickup( SceneNode& node, const TextureHolder& textures ) const {
    auto type = static_cast<Pickup::Type>( randomInt( Pickup::TypeCount ) );

    std::unique_ptr<Pickup> pickup( new Pickup( type, textures ) );
    pickup->setPosition( GetWorldPosition() );
    pickup->SetVelocity( 0.0f, 1.0f );
    node.AttachChild( std::move( pickup ) );
}

void
Aircraft::UpdateTexts() {
    if ( IsDestroyed() ) {
        mHealthDisplay->SetString( "" );
    } else {
        mHealthDisplay->SetString( std::to_string( GetHitpoints() ) + " HP" );
    }
    mHealthDisplay->setPosition( 0.0f, 50.0f );
    mHealthDisplay->setRotation( -getRotation() );

    if ( mMissileDisplay ) {
        if ( mMissileAmmo == 0 || IsDestroyed() ) {
            mMissileDisplay->SetString( "" );
        } else {
            mMissileDisplay->SetString( "M: " + std::to_string( mMissileAmmo ) );
        }
    }
}

void
Aircraft::UpdateRollAnimation() {
    if ( Table[mType].hasRollAnimation ) {
        sf::IntRect textureRect = Table[mType].textureRect;

        if ( GetVelocity().x < 0.0f ) {
            textureRect.left += textureRect.width;
        } else if ( GetVelocity().x > 0.0f ) {
            textureRect.left += 2 * textureRect.width;
        }
        mSprite.setTextureRect( textureRect );
    }
}

SoundEffect::ID
Aircraft::GetRandomExplosionSound() const {
    if ( randomInt( 2 ) == 0 ) {
        return SoundEffect::Explosion1;
    } else {
        return SoundEffect::Explosion2;
    }
}

bool
Aircraft::PickupDropCondition() const {
    bool condition1 = !this->IsAllied();
    bool condition2 = randomInt( 3 ) == 0;
    bool condition3 = !this->mSpawnedPickup;
    bool condition4 = this->mPickupsEnabled;
    return condition1 && condition2 && condition3 && condition4;
}

Projectile::Type
Aircraft::GetBulletType() const {
    if ( this->IsAllied() ) {
        return Projectile::AlliedBullet;
    } else {
        return Projectile::EnemyBullet;
    }
}

float
Aircraft::GetBulletSign() const {
    if ( this->IsAllied() ) {
        return -1.0f;
    } else {
        return +1.0f;
    }
}

SoundEffect::ID
Aircraft::GetGunfireSoundId() const {
    if (this->IsAllied()) {
        return SoundEffect::AlliedGunfire;
    } else {
        return SoundEffect::EnemyGunfire;
    }
}
