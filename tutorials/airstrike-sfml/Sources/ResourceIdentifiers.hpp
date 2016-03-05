
#ifndef __RESOURCE_IDENTIFIERS_HPP__
#define __RESOURCE_IDENTIFIERS_HPP__

// Forward declaration of SFML classes
// TODO: Just include it
namespace sf {
class Texture;
class Font;
class Shader;
class SoundBuffer;
} // namespace sf

namespace Textures {
enum ID {
    Entities,
    Jungle,
    TitleScreen,
    Buttons,
    Explosion,
    Particle,
    FinishLine,
};
} // namespace Textures

namespace Shaders {
enum ID {
    BrightnessPass,
    DownSamplePass,
    GaussianBlurPass,
    AddPass,
};
} // namespace Shaders

namespace Fonts {
enum ID {
    Main,
};
} // namespace Fonts

namespace SoundEffect {
enum ID {
    AlliedGunfire,
    EnemyGunfire,
    Explosion1,
    Explosion2,
    LaunchMissile,
    CollectPickup,
    Button,
};
} // namespace SoundEffect

namespace Music {
enum ID {
    MenuTheme,
    MissionTheme,
};
} // namespace Music

// TODO: proper input
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>           TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>                 FontHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID>             ShaderHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID >   SoundBufferHolder;

#endif // __RESOURCE_IDENTIFIERS_HPP__
