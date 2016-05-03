
#pragma once

#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>


class ERealBox :
    public sf::Transformable,
    public sf::Drawable,
    private sf::NonCopyable {
public:
    ERealBox( b2World& world, sf::Texture& box_texture );

    void UpdateFace();
    void SetVelocity( float vx, float vy );

private:
    void            CenterOrigin( sf::Sprite* sprite );
    virtual void    draw(
        sf::RenderTarget& target,
        sf::RenderStates states
    ) const;

    static const float SCALE;

    sf::Sprite m_face;
    b2Body* m_body;
};
