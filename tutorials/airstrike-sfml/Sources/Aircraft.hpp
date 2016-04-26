
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

    Type            m_type;
    sf::Sprite      m_sprite;
    Animation       m_explosion;
    Command         m_fire_command;
    Command         m_missile_command;
    sf::Time        m_fire_countdown;

    bool            m_is_firing;
    bool            m_is_launching_missile;
    bool            m_show_explosion;
    bool            m_explosion_began;
    bool            m_spawned_pickup;
    bool            m_pickups_enabled;

    int             m_fire_rate_level;
    int             m_spread_level;
    int             m_missile_ammo;

    Command         m_drop_pickup_command;
    float           m_travelled_distance;
    std::size_t     m_direction_index;
    TextNode*       m_health_display;
    TextNode*       m_missile_display;

    int             m_identifier;
};
