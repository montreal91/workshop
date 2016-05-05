
#pragma once

// ih stands for input handler
namespace ih {
enum EeCategory {
    None        = 0,
    Scene       = 1 << 0,
    PlayerShip  = 1 << 1,
    EnemyShip   = 1 << 2,
    Pickup      = 1 << 3,
    Projectile  = 1 << 4,

    SpaceShip   = PlayerShip | EnemyShip,
};

} // namespace ih
