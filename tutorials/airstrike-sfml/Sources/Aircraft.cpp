
#include "Aircraft.hpp"


using namespace std::placeholders;

namespace {
const std::vector<AircraftData> Table = initalizeAircraftData();
} // namespace


Aircraft::Aircraft(
    Type type,
    const TextureHolder& textures,
    const FontHolder& fonts
) :
Entity( Table[type].hitpoints ),
m_type( type ),
m_sprite( textures.get( Table[type].texture ), Table[type].textureRect ),
m_explosion( textures.get( Textures::Explosion ) ),
m_fire_command(),
m_missile_command(),
m_fire_countdown( sf::Time::Zero ),
m_is_firing( false ),
m_is_launching_missile( false ),
m_show_explosion( true ),
m_explosion_began( false ),
m_spawned_pickup( false ),
m_pickups_enabled( true ),
m_fire_rate_level( 1 ),
m_spread_level( 1 ),
m_missile_ammo( 2 ),
m_drop_pickup_command(),
m_travelled_distance( 0.0f ),
m_direction_index( 0 ),
m_health_display( nullptr ),
m_missile_display( nullptr ),
m_identifier( 0 ) {

    this->m_explosion.SetFrameSize( sf::Vector2i( 256, 256 ) );
    this->m_explosion.setNumFrames( 16 );
    this->m_explosion.setDuration( sf::seconds( 1 ) );

    centerOrigin( this->m_sprite );
    centerOrigin( this->m_explosion );

    this->m_fire_command.category       = Category::SceneAirLayer;
    this->m_fire_command.action         = [ this, &textures ] ( SceneNode& node, sf::Time ) {
        this->CreateBullets( node, textures );
    };

    this->m_missile_command.category    = Category::SceneAirLayer;
    this->m_missile_command.action      = [ this, &textures ] ( SceneNode& node, sf::Time ) {
        this->CreateProjectile(
            node,
            Projectile::Missile,
            0.0f, 0.5f,
            textures
        );
    };

    this->m_drop_pickup_command.category = Category::SceneAirLayer;
    this->m_drop_pickup_command.action   = [ this, &textures ] ( SceneNode& node, sf::Time ) {
        this->CreatePickup( node, textures );
    };

    std::unique_ptr<TextNode> healthDisplay( new TextNode( fonts, "" ) );
    this->m_health_display = healthDisplay.get();
    this->AttachChild( std::move( healthDisplay ) );

    if ( GetCategory() == Category::PlayerAircraft ) {
        std::unique_ptr<TextNode> missileDisplay( new TextNode( fonts, "" ) );
        missileDisplay->setPosition( 0, 70 );
        this->m_missile_display = missileDisplay.get();
        this->AttachChild( std::move( missileDisplay ) );
    }
    UpdateTexts();
}

int
Aircraft::GetMissileAmmo() const {
    return this->m_missile_ammo;
}

void
Aircraft::SetMissileAmmo( int ammo ) {
    this->m_missile_ammo = ammo;
}

void
Aircraft::DrawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const {
    if ( IsDestroyed() && this->m_show_explosion ) {
        target.draw( this->m_explosion, states );
    } else {
        target.draw( this->m_sprite, states );
    }
}

void
Aircraft::DisablePickups() {
    this->m_pickups_enabled = false;
}

void
Aircraft::UpdateCurrent( sf::Time dt, CommandQueue& commands ) {
    UpdateTexts();
    UpdateRollAnimation();

    // Entity has been destroyed: Possibly drop pickup, mark for removal
    if ( IsDestroyed() ) {
        this->CheckPickupDrop( commands );
        this->m_explosion.update( dt );

        // Play explosion sound only once
        if ( !this->m_explosion_began ) {
            // Play sound effect
            SoundEffect::ID soundEffect = this->GetRandomExplosionSound();
            this->PlayLocalSound( commands, soundEffect );

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
            this->m_explosion_began = true;
        }
        return;
    }

    this->CheckProjectileLaunch( dt, commands );

    this->UpdateMovementPattern( dt );
    Entity::UpdateCurrent( dt, commands );
}

unsigned int
Aircraft::GetCategory() const {
    if ( this->IsAllied() ) {
        return Category::PlayerAircraft;
    } else {
        return Category::EnemyAircraft;
    }
}

sf::FloatRect
Aircraft::GetBoundingRect() const {
    return GetWorldTransform().transformRect( m_sprite.getGlobalBounds() );
}

bool 
Aircraft::IsMarkedForRemoval() const {
    bool explosion_finished = this->m_explosion.isFinished() || !this->m_show_explosion;
    return this->IsDestroyed() && explosion_finished;
}

void
Aircraft::Remove() {
    Entity::Remove();
    this->m_show_explosion = false;
}

bool
Aircraft::IsAllied() const {
    return m_type == Eagle;
}

float
Aircraft::GetMaxSpeed() const {
    return Table[m_type].speed;
}

void
Aircraft::IncreaseFireRate() {
    if ( this->m_fire_rate_level < 10 ) {
        this->m_fire_rate_level++;
    }
}

void
Aircraft::IncreaseSpread() {
    if ( this->m_spread_level < 3 ) {
        this->m_spread_level++;
    }
}

void
Aircraft::CollectMissiles( unsigned int count ) {
    this->m_missile_ammo += count;
}

void
Aircraft::Fire() {
    // Only ships with fire interval != 0 ate able to fire
    if ( Table[m_type].fireInterval != sf::Time::Zero ) {
        this->m_is_firing = true;
    }
}

void
Aircraft::LaunchMissile() {
    if ( this->m_missile_ammo > 0 ) {
        this->m_is_launching_missile = true;
        this->m_missile_ammo--;
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
    return this->m_identifier;
}

void
Aircraft::SetIdentifier( int identifier ) {
    this->m_identifier = identifier;
}

void
Aircraft::UpdateMovementPattern( sf::Time dt ) {
    // Enemy Airplane: Movement pattern
    const std::vector<Direction>& directions = Table[m_type].directions;
    if ( !directions.empty() ) {
        // Moved long enough in current direction: change direction
        // TODO: put this condition into function
        if ( this->m_travelled_distance > directions[this->m_direction_index].distance ) {
            this->m_direction_index     = ( this->m_direction_index + 1 ) % directions.size();
            this->m_travelled_distance  = 0.0f;
        }

        // Compute velocity from direction
        float radians   = toRadian( directions[this->m_direction_index].angle + 90.0f );
        float vx        = GetMaxSpeed() * std::cos( radians );
        float vy        = GetMaxSpeed() * std::sin( radians );

        this->SetVelocity( vx, vy );

        this->m_travelled_distance += this->GetMaxSpeed() * dt.asSeconds();
    }
}

void
Aircraft::CheckPickupDrop( CommandQueue& commands ) {
    if ( this->PickupDropCondition() ) {
        commands.push( this->m_drop_pickup_command );
    }
    this->m_spawned_pickup = true;
}

void
Aircraft::CheckProjectileLaunch( sf::Time dt, CommandQueue& commands ) {
    // Enemies try to fire all the time
    if ( !this->IsAllied() ) {
        this->Fire();
    }

    // Check for automatic gunfire, allow only in intervals
    // TODO: put this condition into function
    if ( this->m_is_firing && this->m_fire_countdown <= sf::Time::Zero ) {
        commands.push( this->m_fire_command );
        this->PlayLocalSound( commands, this->GetGunfireSoundId() );

        sf::Time time_delta = Table[m_type].fireInterval / ( this->m_fire_rate_level + 1.0f );
        this->m_fire_countdown += time_delta;
        this->m_is_firing = false;
    } else if ( this->m_fire_countdown > sf::Time::Zero ) {
        this->m_fire_countdown -= dt;
        this->m_is_firing = false;
    }

    if ( this->m_is_launching_missile ) {
        commands.push( this->m_missile_command );
        this->PlayLocalSound( commands, SoundEffect::LaunchMissile );
        this->m_is_launching_missile = false;
    }
}

void
Aircraft::CreateBullets( SceneNode& node, const TextureHolder& textures ) const {
    Projectile::Type type = this->GetBulletType();
    switch ( this->m_spread_level ) {
        case 1:
            this->CreateProjectile( node, type, 0.0f, 0.5f, textures );
            break;
        case 2:
            this->CreateProjectile( node, type, -0.33f, 0.33f, textures );
            this->CreateProjectile( node, type, +0.33f, 0.33f, textures );
            break;
        case 3:
            this->CreateProjectile( node, type, -0.5f, 0.33f, textures );
            this->CreateProjectile( node, type, 0.0f, 0.5f, textures );
            this->CreateProjectile( node, type, +0.5f, 0.33f, textures );
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
        xOffset * m_sprite.getGlobalBounds().width,
        yOffset * m_sprite.getGlobalBounds().height
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
        this->m_health_display->SetString( "" );
    } else {
        this->m_health_display->SetString( std::to_string( GetHitpoints() ) + " HP" );
    }
    this->m_health_display->setPosition( 0.0f, 50.0f );
    this->m_health_display->setRotation( -getRotation() );

    if ( this->m_missile_display ) {
        // TODO: put this conditions into functions
        if ( this->m_missile_ammo == 0 || this->IsDestroyed() ) {
            this->m_missile_display->SetString( "" );
        } else {
            this->m_missile_display->SetString(
                "M: " + std::to_string( this->m_missile_ammo )
            );
        }
    }
}

void
Aircraft::UpdateRollAnimation() {
    if ( Table[m_type].hasRollAnimation ) {
        sf::IntRect textureRect = Table[m_type].textureRect;

        if ( this->GetVelocity().x < 0.0f ) {
            textureRect.left += textureRect.width;
        } else if ( this->GetVelocity().x > 0.0f ) {
            textureRect.left += 2 * textureRect.width;
        }
        m_sprite.setTextureRect( textureRect );
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
    bool condition3 = !this->m_spawned_pickup;
    bool condition4 = this->m_pickups_enabled;
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
