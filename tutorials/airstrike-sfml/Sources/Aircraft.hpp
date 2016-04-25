
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

    virtual unsigned int    GetCategory() const;
    virtual sf::FloatRect   GetBoundingRect() const;
    virtual void            Remove();
    virtual bool            IsMarkedForRemoval() const;
    bool                    IsAllied() const;
    float                   GetMaxSpeed() const;
    void                    DisablePickups();

    void                    IncreaseFireRate();
    void                    IncreaseSpread();
    void                    CollectMissiles( unsigned int count );

    void                    Fire();
    void                    LaunchMissile();
    void                    PlayLocalSound(
        CommandQueue& commands,
        SoundEffect::ID effect
    );

    int                     GetIdentifier() const;
    void                    SetIdentifier( int identifier );
    int                     GetMissileAmmo() const;
    void                    SetMissileAmmo( int ammo );

private:
    virtual void        DrawCurrent(
        sf::RenderTarget& target,
        sf::RenderStates states
    ) const;
    virtual void        UpdateCurrent( sf::Time dt, CommandQueue& commands );
    void                UpdateMovementPattern( sf::Time dt );
    void                CheckPickupDrop( CommandQueue& commands );
    void                CheckProjectileLaunch( sf::Time dt, CommandQueue& commands );

    void                CreateBullets(
        SceneNode& node,
        const TextureHolder& textures
    ) const;
    void                CreateProjectile(
        SceneNode& node, 
        Projectile::Type type, 
        float xOffset, 
        float yOffset, 
        const TextureHolder& textures 
    ) const;
    void                CreatePickup(
        SceneNode& node,
        const TextureHolder& textures
    ) const;
    void                UpdateTexts();
    void                UpdateRollAnimation();

    SoundEffect::ID     GetRandomExplosionSound() const;
    bool                PickupDropCondition() const;
    Projectile::Type    GetBulletType() const;

    // Positive for enemies, negative for allies;
    float               GetBulletSign() const;
    SoundEffect::ID     GetGunfireSoundId() const;

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
