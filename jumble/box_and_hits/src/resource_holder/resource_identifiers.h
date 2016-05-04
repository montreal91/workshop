
#pragma once


#include <SFML/Graphics/Texture.hpp>

#include "resource_holder.hpp"

// rh stands for resource holder
namespace rh {
namespace textures {
    enum EeId {
        Box,
        Ground,
    }
} // namespace textures

typedef EtResourceHolder<sf::Texture, textures::EeId> ETextureHolder_t;
} // namespace rh
