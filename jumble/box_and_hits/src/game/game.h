
#pragma once


#include <iostream>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include "world.h"
#include "src/ih/controller.h"


namespace ee {
class EGame : private sf::NonCopyable {
public:
    EGame();
    void Run();

private:
    void ProcessInput();
    void Update( const sf::Time& dt );
    void Render();
    // void UpdateStatistics( const sf::Time& dt );

    static const sf::Time TimePerFrame;

    sf::RenderWindow m_window;
    EWorld m_world;
    // ih::EKeyBinding m_key_binding;
    ih::EController m_controller;

    // sf::Font m_
};

} // namespace ee
