
#include "DataTables.hpp"
#include "Aircraft.hpp"
#include "Projectile.hpp"
#include "Pickup.hpp"


using namespace std::placeholders;

// TODO: load data from external files
std::vector<AircraftData>
initalizeAircraftData() {
    std::vector<AircraftData> data( Aircraft::TypeCount );

    data[Aircraft::Eagle].hitpoints         = 100;
    data[Aircraft::Eagle].speed             = 200.0f;
    data[Aircraft::Eagle].fireInterval      = sf::seconds( 1 );
    data[Aircraft::Eagle].texture           = Textures::Eagle;

    data[Aircraft::Raptor].hitpoints        = 20;
    data[Aircraft::Raptor].speed            = 80.0f;
    data[Aircraft::Raptor].texture          = Textures::Raptor;
    data[Aircraft::Raptor].directions.push_back( Direction( +45.0f, 80.0f ) );
    data[Aircraft::Raptor].directions.push_back( Direction( -45.0f, 160.0f ) );
    data[Aircraft::Raptor].directions.push_back( Direction( +45.0f, 80.0f ) );
    data[Aircraft::Raptor].fireInterval     = sf::seconds( 1.8f );

    data[Aircraft::Avenger].hitpoints       = 40;
    data[Aircraft::Avenger].speed           = 50.0f;
    data[Aircraft::Avenger].texture         = Textures::Avenger;
    data[Aircraft::Avenger].directions.push_back( Direction( +45.0f, 50.0f ) );
    data[Aircraft::Avenger].directions.push_back( Direction( 0.0f, 50.0f ) );
    data[Aircraft::Avenger].directions.push_back( Direction( -45.0f, 100.0f ) );
    data[Aircraft::Avenger].directions.push_back( Direction( 0.0f, 50.0f ) );
    data[Aircraft::Avenger].directions.push_back( Direction( +45.0f, 50.0f ) );
    data[Aircraft::Avenger].fireInterval    = sf::Time::Zero;

    return data;
}

std::vector<ProjectileData>
initalizeProjectileData() {
    std::vector<ProjectileData> data( Projectile::TypeCount );
    data[Projectile::AlliedBullet].damage   = 10;
    data[Projectile::AlliedBullet].speed    = 300.0f;
    data[Projectile::AlliedBullet].texture  = Textures::Bullet;

    data[Projectile::EnemyBullet].damage    = 10;
    data[Projectile::EnemyBullet].speed     = 300.0f;
    data[Projectile::EnemyBullet].texture   = Textures::Bullet;

    data[Projectile::Missile].damage        = 200;
    data[Projectile::Missile].speed         = 150.0f;
    data[Projectile::Missile].texture       = Textures::Missile;

    return data;
}

std::vector<PickupData>
initalizePickupData() {
    std::vector<PickupData> data( Pickup::TypeCount );

    data[Pickup::HealthRefill].texture  = Textures::HealthRefill;
    data[Pickup::HealthRefill].action   = [] ( Aircraft& a ) { a.repair( 25 ); };

    data[Pickup::MissileRefill].texture = Textures::MissileRefill;
    data[Pickup::MissileRefill].action  = std::bind( &Aircraft::collectMissiles, _1, 3 );

    data[Pickup::FireSpread].texture    = Textures::FireSpread;
    data[Pickup::FireSpread].action     = std::bind( &Aircraft::increaseSpread, _1 );

    data[Pickup::FireRate].texture      = Textures::FireRate;
    data[Pickup::FireRate].action       = std::bind( &Aircraft::increaseFireRate, _1 );

    return data;
}
