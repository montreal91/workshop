
#ifndef __PICKUP_HPP__
#define __PICKUP_HPP__


#include "Entity.hpp"
#include "Command.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>


// TODO: replace it with a proper import 
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
    virtual unsigned int    getCategory() const;
    virtual sf::FloatRect   getBoundingRect() const;

    void                    apply( Aircraft& player ) const;

protected:
    virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;

private:
    Type        mType;
    sf::Sprite  mSprite;

};

#endif // __PICKUP_HPP__
