
#pragma once

// ih stands for input handler
namespace ih {
enum EeCategory {
    None        = 0,
    PlayerShip  = 1 << 0,
    EnemyShip   = 1 << 1,
    Pickup      = 1 << 2,
    Projectile  = 1 << 3,

    SpaceShip   = PlayerShip | EnemyShip,
};

} // namespace ih
