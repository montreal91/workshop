
//TODO: move this shit to external file

#ifndef __DATA_TABLES_HPP__
#define __DATA_TABLES_HPP__


#include "ResourceIdentifiers.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>

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
    sf::Time                fireInterval;
    std::vector<Direction>  directions;
};

struct ProjectileData {
    int             damage;
    float           speed;
    Textures::ID    texture;
};

struct PickupData {
    std::function<void( Aircraft& )>    action;
    Textures::ID                        texture;
};


std::vector<AircraftData>   initalizeAircraftData();
std::vector<ProjectileData> initalizeProjectileData();
std::vector<PickupData>     initalizePickupData();

#endif
