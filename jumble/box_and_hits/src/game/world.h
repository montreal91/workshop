
#pragma once


#include <algorithm>
#include <array>
#include <cmath>
#include <queue>

#include <Box2D/Box2D.h>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>

#include "src/ih/command_queue.h"
#include "src/ih/command.h"
#include "src/nodes/entity.h"
#include "src/nodes/scene_node.h"
#include "src/nodes/sprite_node.h"
#include "src/resource_holder/resource_holder.h"
#include "src/resource_holder/resource_identifiers.h"


// ee stands for Epic Eagle
namespace ee {
class EWorld : private sf::NonCopyable {
public:
    explicit            EWorld( sf::RenderWindow& window );

    void                Update( const sf::Time& dt );
    void                Draw();

    ih::ECommandQueue&  GetCommandQueue();

private:
    void CreatePhysicalWorld();
    void LoadTextures();
    void BuildScene();

    enum EeLayer {
        Background,
        Air,
        LayerCount,
    };

    b2World                             m_physical_world;

    sf::RenderWindow&                   m_window;
    sf::View                            m_world_view;
    rh::ETextureHolder_t                m_textures;

    nodes::ESceneNode                   m_scene_graph;
    std::array<ESceneNode*, LayerCount> m_scene_layers;
    ih::ECommandQueue                   m_command_queue;

    nodes::EEntity*                     m_player_box;
};

} // namespace ee
