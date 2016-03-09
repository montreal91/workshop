
#include "Entity.hpp"


Entity::Entity( int hitpoints ) :
mVelocity(),
mHitpoints( hitpoints ) {
}

void
Entity::SetVelocity( sf::Vector2f velocity ) {
    mVelocity = velocity;
}

void
Entity::SetVelocity( float vx, float vy ) {
    mVelocity.x = vx;
    mVelocity.y = vy;
}

sf::Vector2f
Entity::GetVelocity() const {
    return mVelocity;
}

void
Entity::Accelerate( sf::Vector2f velocity ) {
    mVelocity += velocity;
}

void
Entity::Accelerate( float vx, float vy ) {
    mVelocity.x += vx;
    mVelocity.y += vy;
}

int
Entity::GetHitpoints() const {
    return mHitpoints;
}

void
Entity::SetHitpoints( int points ) {
    assert( points > 0 );
    mHitpoints = points;
}

void
Entity::Repair( int points ) {
    assert( points > 0 );
    mHitpoints += points;
}

void
Entity::Damage( int points ) {
    assert( points > 0 );
    mHitpoints -= points;
}

void
Entity::Destroy() {
    mHitpoints = 0;
}

void
Entity::Remove() {
    Destroy();
}

bool
Entity::IsDestroyed() const {
    return mHitpoints <= 0;
}

void
Entity::UpdateCurrent( sf::Time dt, CommandQueue& commands ) {
    move( mVelocity * dt.asSeconds() );
}
