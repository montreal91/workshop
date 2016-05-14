
#pragma once

#include <Box2D/Box2D.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "scene_node.h"


namespace nodes {
class EEntity : public ESceneNode {
public:
    explicit        EEntity(
        b2World& world,
        const b2BodyType body_type,
        sf::Texture& texture,
        float phys_width,
        float phys_height
    );
    // void            SetVelocity( const sf::Vector2f& velocity );
    void            SetVelocity( float vx, float vy );
    void            Accelerate( const b2Vec2& dv );
    void            Accelerate( float dvx, float dvy );

    static const float  SCALE;

    b2Vec2          GetVelocity() const;

private:
    static void     CenterOrigin( sf::Sprite* sprite );
    virtual void    UpdateCurrent( const sf::Time& dt );
    virtual void    DrawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;
    void            UpdateSprite();


    b2Vec2          m_velocity;
    sf::Sprite      m_sprite;
    b2Body*         m_body;
};

} // namespace nodes
