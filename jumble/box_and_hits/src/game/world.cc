
#include "world.h"
#include <iostream>

namespace ee {
EWorld::EWorld( sf::RenderWindow& window ) :
m_physical_world( b2Vec2( 0, 10.0f ) ),
m_window( window ),
m_world_view( window.getDefaultView() ),
m_textures(),
m_scene_layers(),
m_player_box( nullptr ) {
    this->LoadTextures();
    this->BuildScene();
}

void
EWorld::Update( const sf::Time& dt ) {
    this->m_physical_world.Step( 1 / 60, 8, 3 );

    while ( !this->m_command_queue.IsEmpty() ) {
        this->m_scene_graph.OnCommand( this->m_command_queue.Pop(), dt );
    }

    this->m_scene_graph.Update( dt );
}

void
EWorld::Draw() {
    // std::cout << "2";
    this->m_window.clear(sf::Color::Black);
    // this->m_window.setView( this->m_world_view );
    // this->m_window.draw( this->m_scene_graph );
}

ih::ECommandQueue&
EWorld::GetCommandQueue() {
    return this->m_command_queue;
}

void
EWorld::LoadTextures() {
    this->m_textures.Load( rh::textures::Box, "media/sprites/box.png" );
    this->m_textures.Load( rh::textures::Ground, "media/sprites/ground.png" );
}

void
EWorld::CreatePhysicalWorld() {
    b2Vec2 gravity( 0.0f, 10.0f );
    this->m_physical_world = b2World( gravity );
}

void
EWorld::BuildScene() {
    std::unique_ptr<nodes::EEntity> pb(
        new nodes::EEntity(
            this->m_physical_world,
            b2_dynamicBody,
            this->m_textures.Get(rh::textures::Box),
            0.5333f, 0.5333f));
    this->m_player_box = pb.get();
    // this->m_player_box->SetPosition(mSpawnPosition);
    // mSceneLayers[Air]->attachChild(std::move(pb));
    this->m_scene_graph.AttachChild( std::move(pb ) );
}

} // namespace ee