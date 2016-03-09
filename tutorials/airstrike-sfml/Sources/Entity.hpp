
#pragma once


#include <cassert>

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include "CommandQueue.hpp"
#include "SceneNode.hpp"


class Entity : public SceneNode {
public:
    explicit        Entity( int hitpoints );

    void            SetVelocity( sf::Vector2f velocity );
    void            SetVelocity( float vx, float vy );
    void            Accelerate( sf::Vector2f velocity );
    void            Accelerate( float vx, float vy );
    sf::Vector2f    GetVelocity() const;

    int             GetHitpoints() const;
    void            SetHitpoints( int points );
    void            Repair( int points );
    void            Damage( int points );
    void            Destroy();
    virtual void    Remove();
    virtual bool    IsDestroyed() const;

protected:
    virtual void    UpdateCurrent( sf::Time dt, CommandQueue& commands );

private:
    sf::Vector2f    mVelocity;
    int             mHitpoints;
};
