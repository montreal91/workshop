
#include "game.h"

// Epic Eagle
namespace ee {
const sf::Time EGame::TimePerFrame = sf::seconds( 1.0f / 60.0f );

EGame::EGame() :
m_window( sf::VideoMode( 800, 600 ), "Controlled Physical world", sf::Style::Close ),
m_world( m_window ),
m_controller() {
    this->m_window.setKeyRepeatEnabled( false );
}

void
EGame::Run() {
    sf::Clock clock;
    sf::Time time_since_last_update = sf::Time::Zero;
    while ( this->m_window.isOpen() ) {
        sf::Time elapsed_time = clock.restart();
        time_since_last_update += elapsed_time;
        while ( time_since_last_update > TimePerFrame ) {
            time_since_last_update -= TimePerFrame;
            this->ProcessInput();
            this->Update( TimePerFrame ); // ???
        }
        this->Render();
    }
}

void
EGame::ProcessInput() {
    ih::ECommandQueue& commands = this->m_world.GetCommandQueue();
    std::cout << "p";
    sf::Event event;
    while ( this->m_window.pollEvent( event ) ) {
        this->m_controller.HandleEvent( event, commands );

        if ( event.type == sf::Event::Closed ) {
            this->m_window.close();
        }
        if ( event.key.code == sf::Keyboard::Escape ) {
            this->m_window.close();
        }
        if ( event.key.code == sf::Keyboard::P ) {
            std::cout << "q";
        }
    }
    this->m_controller.HandleRealtimeInput( commands );
}

void
EGame::Update( const sf::Time& dt ) {
    this->m_world.Update( dt );
}

void
EGame::Render() {
    this->m_world.Draw();
}
} // namespace ee
