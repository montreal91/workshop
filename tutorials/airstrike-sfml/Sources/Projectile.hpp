
#pragma once


#include <cassert>
#include <cmath>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Entity.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Utility.hpp"


class Projectile : public Entity {
public:
    enum Type {
        AlliedBullet,
        EnemyBullet,
        Missile,
        TypeCount,
    };

    Projectile( Type type, const TextureHolder& textures );

    void                    GuideTowards( sf::Vector2f position );
    bool                    IsGuided() const;

    virtual unsigned int    GetCategory() const;
    virtual sf::FloatRect   GetBoundingRect() const;
    float                   GetMaxSpeed() const;
    int                     GetDamage() const;

private:
    virtual void    UpdateCurrent( sf::Time dt, CommandQueue& commands );
    virtual void    DrawCurrent(
        sf::RenderTarget& target,
        sf::RenderStates states
    ) const;

    Type            mType;
    sf::Sprite      mSprite;
    sf::Vector2f    mTargetDirection;
};
