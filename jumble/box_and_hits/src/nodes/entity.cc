
#include "entity.h"


namespace nodes {

const float EEntity::SCALE = 30.0f;

EEntity::EEntity(
    b2World& world,
    const b2BodyType& body_type,
    sf::Texture& texture,
    float phys_width,
    float phys_height,
    const b2Vec2& position ) :
m_velocity() {
    b2BodyDef BodyDef;
    BodyDef.position    = position;
    BodyDef.type        = body_type;

    this->m_body        = world.CreateBody( &BodyDef );

    b2PolygonShape Shape;
    Shape.SetAsBox( phys_width, phys_height );
    b2FixtureDef FixtureDef;
    FixtureDef.density  = 1.0f;
    FixtureDef.friction = 0.7f;
    FixtureDef.shape    = &Shape;
    this->m_body->CreateFixture( &FixtureDef );

    this->m_sprite.setTexture( texture );

    // AD-HOC solution.
    // Probably, the problem is with the size of the ground body
    if ( body_type == b2_dynamicBody ) {
        this->CenterOrigin( &this->m_sprite );
    } else {
        this->m_sprite.setOrigin(400.0f, 8.0f);
    }
    this->UpdateSprite();
}

// void
// EEntity::SetVelocity( const sf::Vector2f& velocity ) {
//     this->m_velocity = velocity;
// }

void
EEntity::SetVelocity( float vx, float vy ) {
    this->m_velocity.x = vx;
    this->m_velocity.y = vy;
}

void
EEntity::Accelerate( const b2Vec2& dv ) {
    std::cout << "e";
    this->m_velocity += dv;
    this->m_body->SetLinearVelocity( this->m_velocity );
}

void
EEntity::Accelerate( float dvx, float dvy ) {
    this->m_velocity.x += dvx;
    this->m_velocity.y += dvy;
}

b2Vec2
EEntity::GetVelocity() const {
    return this->m_velocity;
}

void
EEntity::CenterOrigin(sf::Sprite* sprite) {
    sf::FloatRect bounds = sprite->getLocalBounds();
    sprite->setOrigin(
        std::floor( bounds.left + bounds.width / 2.0f ),
        std::floor( bounds.top + bounds.height / 2.0f )
    );
}

void
EEntity::UpdateCurrent( const sf::Time& ) {
    this->UpdateSprite();
}

void
EEntity::DrawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.draw( this->m_sprite );
}

void
EEntity::UpdateSprite() {
    b2Vec2 pos = this->m_body->GetPosition();
    this->m_sprite.setPosition( SCALE * pos.x, SCALE * pos.y );
}

} // namespace nodes
