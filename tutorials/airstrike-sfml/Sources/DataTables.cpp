
#include "DataTables.hpp"
#include "Aircraft.hpp"
#include "Projectile.hpp"
#include "Pickup.hpp"
#include "Particle.hpp"


using namespace std::placeholders;

// TODO: load data from external files
std::vector<AircraftData>
initalizeAircraftData() {
    std::vector<AircraftData> data( Aircraft::TypeCount );

    data[Aircraft::Eagle].hitpoints         = 100;
    data[Aircraft::Eagle].speed             = 200.0f;
    data[Aircraft::Eagle].fireInterval      = sf::seconds( 1 );
    data[Aircraft::Eagle].texture           = Textures::Entities;
    data[Aircraft::Eagle].textureRect       = sf::IntRect( 0, 0, 48, 64 );
    data[Aircraft::Eagle].hasRollAnimation  = true;

    data[Aircraft::Raptor].hitpoints        = 20;
    data[Aircraft::Raptor].speed            = 80.0f;
    data[Aircraft::Raptor].texture          = Textures::Entities;
    data[Aircraft::Raptor].textureRect      = sf::IntRect( 144, 0, 84, 64 );
    data[Aircraft::Raptor].directions.push_back( Direction( +45.0f, 80.0f ) );
    data[Aircraft::Raptor].directions.push_back( Direction( -45.0f, 160.0f ) );
    data[Aircraft::Raptor].directions.push_back( Direction( +45.0f, 80.0f ) );
    data[Aircraft::Raptor].fireInterval     = sf::Time::Zero;
    data[Aircraft::Raptor].hasRollAnimation = false;


    data[Aircraft::Avenger].hitpoints           = 40;
    data[Aircraft::Avenger].speed               = 50.0f;
    data[Aircraft::Avenger].texture             = Textures::Entities;
    data[Aircraft::Avenger].textureRect         = sf::IntRect( 289, 3, 60, 57 );
    data[Aircraft::Avenger].directions.push_back( Direction( +45.0f, 50.0f ) );
    data[Aircraft::Avenger].directions.push_back( Direction( 0.0f, 50.0f ) );
    data[Aircraft::Avenger].directions.push_back( Direction( -45.0f, 100.0f ) );
    data[Aircraft::Avenger].directions.push_back( Direction( 0.0f, 50.0f ) );
    data[Aircraft::Avenger].directions.push_back( Direction( +45.0f, 50.0f ) );
    data[Aircraft::Avenger].fireInterval        = sf::seconds( 2 );
    data[Aircraft::Avenger].hasRollAnimation    = false;

    return data;
}

std::vector<ProjectileData>
initalizeProjectileData() {
    std::vector<ProjectileData> data( Projectile::TypeCount );
    data[Projectile::AlliedBullet].damage       = 10;
    data[Projectile::AlliedBullet].speed        = 300.0f;
    data[Projectile::AlliedBullet].texture      = Textures::Entities;
    data[Projectile::AlliedBullet].textureRect  = sf::IntRect( 175, 64, 3, 14 );

    data[Projectile::EnemyBullet].damage        = 10;
    data[Projectile::EnemyBullet].speed         = 300.0f;
    data[Projectile::EnemyBullet].texture       = Textures::Entities;
    data[Projectile::EnemyBullet].textureRect   = sf::IntRect( 178, 64, 3, 14 );


    data[Projectile::Missile].damage            = 200;
    data[Projectile::Missile].speed             = 150.0f;
    data[Projectile::Missile].texture           = Textures::Entities;
    data[Projectile::Missile].textureRect       = sf::IntRect( 160, 64, 15, 32 );

    return data;
}

std::vector<PickupData>
initalizePickupData() {
    std::vector<PickupData> data( Pickup::TypeCount );

    data[Pickup::HealthRefill].texture      = Textures::Entities;
    data[Pickup::HealthRefill].textureRect  = sf::IntRect( 0, 64, 40, 40 );
    data[Pickup::HealthRefill].action       = [] ( Aircraft& a ) { a.repair( 25 ); };

    data[Pickup::MissileRefill].texture     = Textures::Entities;
    data[Pickup::MissileRefill].textureRect = sf::IntRect( 40, 64, 40, 40 );
    data[Pickup::MissileRefill].action      = std::bind( &Aircraft::collectMissiles, _1, 3 );

    data[Pickup::FireSpread].texture        = Textures::Entities;
    data[Pickup::FireSpread].textureRect    = sf::IntRect( 80, 64, 40, 40 );
    data[Pickup::FireSpread].action         = std::bind( &Aircraft::increaseSpread, _1 );

    data[Pickup::FireRate].texture          = Textures::Entities;
    data[Pickup::FireRate].textureRect      = sf::IntRect( 120, 64, 40, 40 );
    data[Pickup::FireRate].action           = std::bind( &Aircraft::increaseFireRate, _1 );

    return data;
}

std::vector<ParticleData>
initalizeParticleData() {
    std::vector<ParticleData> data( Particle::ParticleCount );

    data[Particle::Propellant].color    = sf::Color( 255, 255, 50 );
    data[Particle::Propellant].lifetime = sf::seconds( 0.6f );

    data[Particle::Smoke].color         = sf::Color( 50, 50, 50 );
    data[Particle::Smoke].lifetime      = sf::seconds( 4.0f );

    return data;
}
