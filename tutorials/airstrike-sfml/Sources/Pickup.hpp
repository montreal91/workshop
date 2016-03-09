
#pragma once


#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

// #include "Aircraft.hpp"
#include "Category.hpp"
#include "Command.hpp"
#include "DataTables.hpp"
#include "Entity.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Utility.hpp"


// TODO: replace it with a proper import
// ??? Replacement produces a compile-time error
class Aircraft;

class Pickup : public Entity {
public:
    enum Type {
        HealthRefill,
        MissileRefill,
        FireSpread,
        FireRate,
        TypeCount,
    };

    Pickup( Type type, const TextureHolder& textures );

    virtual unsigned int    GetCategory() const;
    virtual sf::FloatRect   GetBoundingRect() const;

    void                    Apply( Aircraft& player ) const;

protected:
    virtual void DrawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;

private:
    Type        mType;
    sf::Sprite  mSprite;
};
