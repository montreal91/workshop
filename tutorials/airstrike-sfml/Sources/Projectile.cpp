
#include "Projectile.hpp"
#include "EmitterNode.hpp"
#include "DataTables.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <cassert>


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
    if ( isGuided() ) {
        std::unique_ptr<EmitterNode> smoke( new EmitterNode( Particle::Smoke ) );
        smoke->setPosition( 0.0f, getBoundingRect().height / 2.0f );
        attachChild( std::move( smoke ) );

        std::unique_ptr<EmitterNode> propellant(
            new EmitterNode( Particle::Propellant )
        );
        propellant->setPosition( 0.0f, getBoundingRect().height / 2.0f );
        attachChild( std::move( propellant ) );
    }
}

void
Projectile::guideTowards( sf::Vector2f position ) {
    assert( isGuided() );
    mTargetDirection = unitVector( position - getWorldPosition() );
}

bool
Projectile::isGuided() const {
    return mType == Missile;
}

void
Projectile::updateCurrent( sf::Time dt, CommandQueue& commands ) {
    if ( isGuided() ) {
        const float approachRate = 200.0f;

        sf::Vector2f newVelocity = unitVector(
            approachRate * dt.asSeconds() * mTargetDirection + getVelocity()
        );
        newVelocity *= getMaxSpeed();
        float angle = std::atan2( newVelocity.y, newVelocity.x );

        setRotation( toDegree( angle ) + 90.0f );
        setVelocity( newVelocity );
    }

    Entity::updateCurrent( dt, commands );
}

void
Projectile::drawCurrent(
    sf::RenderTarget& target,
    sf::RenderStates states
) const {
    target.draw( mSprite, states );
}

unsigned int
Projectile::getCategory() const {
    if ( mType == EnemyBullet ) return Category::EnemyProjectile;
    else return Category::AlliedProjectile;
}

sf::FloatRect
Projectile::getBoundingRect() const {
    return getWorldTransform().transformRect( mSprite.getGlobalBounds() );
}

float
Projectile::getMaxSpeed() const {
    return Table[mType].speed;
}

int
Projectile::getDamage() const {
    return Table[mType].damage;
}
