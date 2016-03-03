
//TODO: move this shit to external file

#ifndef __DATA_TABLES_HPP__
#define __DATA_TABLES_HPP__


#include "ResourceIdentifiers.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <functional>


class Aircraft;


struct Direction {
    Direction( float angle, float distance ) :
    angle( angle ),
    distance( distance ) {
    }

    float angle;
    float distance;
};

struct AircraftData {
    int                     hitpoints;
    float                   speed;
    Textures::ID            texture;
    sf::IntRect             textureRect;
    sf::Time                fireInterval;
    std::vector<Direction>  directions;
    bool                    hasRollAnimation;
};

struct ProjectileData {
    int             damage;
    float           speed;
    Textures::ID    texture;
    sf::IntRect     textureRect;
};

struct PickupData {
    std::function<void( Aircraft& )>    action;
    Textures::ID                        texture;
    sf::IntRect                         textureRect;
};

struct ParticleData {
    sf::Color color;
    sf::Time lifetime;
};


std::vector<AircraftData>   initalizeAircraftData();
std::vector<ProjectileData> initalizeProjectileData();
std::vector<PickupData>     initalizePickupData();
std::vector<ParticleData>   initalizeParticleData();

#endif // __DATA_TABLES_HPP__
