
#pragma once

#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>

#include "scene_node.h"

namespace nodes {
class ERealBox : public ESceneNode {
public:
    ERealBox( b2World& world, sf::Texture& box_texture );

    void    UpdateFace();
    void    SetVelocity( float vx, float vy );
    void    Accelerate( const b2Vec2& dv );
    int     GetIdentifier() const;
    float   GetMaxSpeed() const;

private:
    void            CenterOrigin( sf::Sprite* sprite );
    virtual void    draw(
        sf::RenderTarget& target,
        sf::RenderStates states
    ) const;

    static const float SCALE;

    sf::Sprite  m_face;
    b2Body*     m_body;
    int         m_id;
    float       m_max_speed;
};

} // namespace nodes
