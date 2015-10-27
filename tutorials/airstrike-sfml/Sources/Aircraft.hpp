
#ifndef __AIRCRAFT_HPP__
#define __AIRCRAFT_HPP__

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>

class Aircraft : public Entity {
public:
    enum Type {
        Eagle,
        Raptor,
    };

    Aircraft( Type type, const TextureHolder& textures );

    virtual unsigned int getCategory() const;

private:
    virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;

    Type mType;
    sf::Sprite mSprite;

};

#endif
