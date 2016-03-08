
#pragma once


#include <cmath>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Animation.hpp"
#include "Command.hpp"
#include "CommandQueue.hpp"
#include "DataTables.hpp"
#include "Entity.hpp"
#include "NetworkNode.hpp"
#include "Pickup.hpp"
#include "Projectile.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SoundNode.hpp"
#include "TextNode.hpp"
#include "Utility.hpp"


class Aircraft : public Entity {
public:
    enum Type {
        Eagle,
        Raptor,
        Avenger,
        TypeCount,
    };

    Aircraft( Type type, const TextureHolder& textures, const FontHolder& fonts );

    virtual unsigned int    getCategory() const;
    virtual sf::FloatRect   getBoundingRect() const;
    virtual void            remove();
    virtual bool            isMarkedForRemoval() const;
    bool                    isAllied() const;
    float                   getMaxSpeed() const;
    void                    disablePickups();

    void                    increaseFireRate();
    void                    increaseSpread();
    void                    collectMissiles( unsigned int count );

    void                    fire();
    void                    launchMissile();
    void                    playLocalSound( CommandQueue& commands, SoundEffect::ID effect );

    int                     getIdentifier(); // TODO const
    void                    setIdentifier( int identifier );
    int                     getMissileAmmo() const;
    void                    setMissileAmmo( int ammo );

private:
    virtual void    drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;
    virtual void    updateCurrent( sf::Time dt, CommandQueue& commands );
    void            updateMovementPattern( sf::Time dt );
    void            checkPickupDrop( CommandQueue& commands );
    void            checkProjectileLaunch( sf::Time dt, CommandQueue& commands );

    void            createBullets( SceneNode& node, const TextureHolder& textures ) const;
    void            createProjectile( 
        SceneNode& node, 
        Projectile::Type type, 
        float xOffset, 
        float yOffset, 
        const TextureHolder& textures 
    ) const;
    void            createPickup( SceneNode& node, const TextureHolder& textures ) const;
    void            updateTexts();
    void            updateRollAnimation();

    Type            mType;
    sf::Sprite      mSprite;
    Animation       mExplosion;
    Command         mFireCommand;
    Command         mMissileCommand;
    sf::Time        mFireCountdown;

    bool            mIsFiring;
    bool            mIsLaunchingMissile;
    bool            mShowExplosion;
    bool            mExplosionBegan;
    bool            mSpawnedPickup;
    bool            mPickupsEnabled;

    int             mFireRateLevel;
    int             mSpreadLevel;
    int             mMissileAmmo;

    Command         mDropPickupCommand;
    float           mTravelledDistance;
    std::size_t     mDirectionIndex;
    TextNode*       mHealthDisplay;
    TextNode*       mMissileDisplay;

    int             mIdentifier;
};
