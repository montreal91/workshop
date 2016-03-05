
#ifndef __PROJECTILE_HPP__
#define __PROJECTILE_HPP__


#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>


class Projectile : public Entity {
public:
    enum Type {
        AlliedBullet,
        EnemyBullet,
        Missile,
        TypeCount,
    };

    Projectile( Type type, const TextureHolder& textures );

    void                    guideTowards( sf::Vector2f position );
    bool                    isGuided() const;

    virtual unsigned int    getCategory() const;
    virtual sf::FloatRect   getBoundingRect() const;
    float                   getMaxSpeed() const;
    int                     getDamage() const;

private:
    virtual void    updateCurrent( sf::Time dt, CommandQueue& commands );
    virtual void    drawCurrent(
        sf::RenderTarget& target,
        sf::RenderStates states
    ) const;

    Type            mType;
    sf::Sprite      mSprite;
    sf::Vector2f    mTargetDirection;

};

#endif
