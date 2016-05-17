
#pragma once

#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>


class CwGame : private sf::NonCopyable {
public:
    CwGame();

    void Run();

private:
    void            ProcessEvents();
    void            ApplyVortexRotation( const sf::Time& dt );
    void            GuideCopter( const sf::Time& dt );
    void            Update( const sf::Time& dt );
    void            Render();

    void            HandlePlayerInput( sf::Keyboard::Key key, bool is_pressed );

    void            NormalizeVector( sf::Vector2f* vec ) const;
    sf::Vector2f    GetOrthogonalVector( const sf::Vector2f& vec ) const;

    static const float          PLAYER_SPEED;
    static const float          COPTER_SPEED;
    static const float          VORTEX_ANGULAR_SPEED;
    static const sf::Vector2f   VORTEX_CENTER;
    static const sf::Time       TIME_PER_FRAME;

    sf::RenderWindow    m_window;
    sf::CircleShape     m_player;
    sf::CircleShape     m_copter;

    bool                m_is_moving_up;
    bool                m_is_moving_down;
    bool                m_is_moving_left;
    bool                m_is_moving_right;
};
