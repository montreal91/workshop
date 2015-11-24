
#ifndef __RESOURCE_IDENTIFIERS_HPP__
#define __RESOURCE_IDENTIFIERS_HPP__

// Forward declaration of SFML classes
namespace sf {
    class Texture;
    class Font;
}

namespace Textures {
enum ID {
    Eagle,
    Raptor,
    Avenger,
    Bullet,
    Missile,
    Desert,
    HealthRefill,
    MissileRefill,
    FireSpread,
    FireRate,
    TitleScreen,
    ButtonNormal,
    ButtonSelected,
    ButtonPressed,
};
} // namespace Textures

namespace Fonts {
enum ID {
    Main,
};
} // namespace Fonts

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>   TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>         FontHolder;

#endif
