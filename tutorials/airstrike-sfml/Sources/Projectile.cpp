
#include "Projectile.hpp"
#include "EmitterNode.hpp" // ??? Why this two includes
#include "DataTables.hpp" // MUST be here and not in header


namespace {
const std::vector<ProjectileData> Table = initalizeProjectileData();
} // namespace

Projectile::Projectile( Type type, const TextureHolder& textures ) :
Entity( 1 ),
mType( type ),
mSprite( textures.get( Table[type].texture ), Table[type].textureRect ),
mTargetDirection() {
    centerOrigin( mSprite );

    // Add particle system for missiles
    // TODO: put it into function
    if ( IsGuided() ) {
        std::unique_ptr<EmitterNode> smoke( new EmitterNode( Particle::Smoke ) );
        smoke->setPosition( 0.0f, GetBoundingRect().height / 2.0f );
        AttachChild( std::move( smoke ) );

        std::unique_ptr<EmitterNode> propellant(
            new EmitterNode( Particle::Propellant )
        );
        propellant->setPosition( 0.0f, GetBoundingRect().height / 2.0f );
        AttachChild( std::move( propellant ) );
    }
}

void
Projectile::GuideTowards( sf::Vector2f position ) {
    assert( IsGuided() );
    mTargetDirection = unitVector( position - GetWorldPosition() );
}

bool
Projectile::IsGuided() const {
    return mType == Missile;
}

void
Projectile::UpdateCurrent( sf::Time dt, CommandQueue& commands ) {
    if ( IsGuided() ) {
        const float approachRate = 200.0f;

        sf::Vector2f newVelocity = unitVector(
            approachRate * dt.asSeconds() * mTargetDirection + GetVelocity()
        );
        newVelocity *= GetMaxSpeed();
        float angle = std::atan2( newVelocity.y, newVelocity.x );

        setRotation( toDegree( angle ) + 90.0f );
        SetVelocity( newVelocity );
    }

    Entity::UpdateCurrent( dt, commands );
}

void
Projectile::DrawCurrent(
    sf::RenderTarget& target,
    sf::RenderStates states
) const {
    target.draw( mSprite, states );
}

unsigned int
Projectile::GetCategory() const {
    if ( mType == EnemyBullet ) return Category::EnemyProjectile;
    else return Category::AlliedProjectile;
}

sf::FloatRect
Projectile::GetBoundingRect() const {
    return GetWorldTransform().transformRect( mSprite.getGlobalBounds() );
}

float
Projectile::GetMaxSpeed() const {
    return Table[mType].speed;
}

int
Projectile::GetDamage() const {
    return Table[mType].damage;
}
