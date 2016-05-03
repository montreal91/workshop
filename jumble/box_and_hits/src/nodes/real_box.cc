
#include "real_box.h"

const float ERealBox::SCALE = 30.0f;

ERealBox::ERealBox( b2World& world, sf::Texture& box_texture ) {
    b2BodyDef BodyDef;
    BodyDef.position    = b2Vec2( 10, 0 );
    BodyDef.type        = b2_dynamicBody;

    this->m_body        = world.CreateBody( &BodyDef );

    b2PolygonShape Shape;
    Shape.SetAsBox( ( 32.0f / 2 ) / SCALE, ( 32.0f / 2 ) / SCALE );
    b2FixtureDef FixtureDef;
    FixtureDef.density  = 1.0f;
    FixtureDef.friction = 0.7f;
    FixtureDef.shape    = &Shape;
    this->m_body->CreateFixture( &FixtureDef );

    this->m_face.setTexture( box_texture );
    this->CenterOrigin( &this->m_face );

    this->UpdateFace();
}

void
ERealBox::UpdateFace() {
    b2Vec2 pos = this->m_body->GetPosition();
    this->m_face.setPosition( SCALE * pos.x, SCALE * pos.y );
    this->m_face.setRotation( this->m_body->GetAngle() * 180 / b2_pi );
}

void
ERealBox::SetVelocity(float vx, float vy) {
    this->m_body->SetLinearVelocity( b2Vec2( vx, vy ) );
}

void
ERealBox::CenterOrigin(sf::Sprite* sprite) {
    sf::FloatRect bounds = sprite->getLocalBounds();
    sprite->setOrigin(
        std::floor( bounds.left + bounds.width / 2.0f ),
        std::floor( bounds.top + bounds.height / 2.0f )
    );
}

void
ERealBox::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.draw( this->m_face, states );
}
