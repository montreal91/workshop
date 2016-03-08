
#pragma once


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "ResourceHolder.hpp"

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

typedef ResourceHolder<sf::Texture, Textures::ID>           TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>                 FontHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID>             ShaderHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID >   SoundBufferHolder;
