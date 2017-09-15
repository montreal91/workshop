
#pragma once

#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "zero_finder.h"


class CwGame : private sf::NonCopyable {
public:
    CwGame();

    void Run();

    static const float          PLAYER_SPEED;
    static const float          COPTER_SPEED;
    static const float          VORTEX_ANGULAR_SPEED;
    static const sf::Vector2f   VORTEX_CENTER;

private:
    void            ProcessEvents();
    void            ApplyVortexRotation(const sf::Time& dt);
    void            GuideCopter(const sf::Time& dt);
    void            Update(const sf::Time& dt);
    void            Render();
    void            UpdateStatistics(const sf::Time& dt);

    void            HandlePlayerInput(sf::Keyboard::Key key, bool is_pressed);

    void            NormalizeVector(sf::Vector2f* vec) const;

    static const sf::Time       TIME_PER_FRAME;

    sf::RenderWindow    m_window;
    sf::CircleShape     m_player;
    sf::CircleShape     m_copter;
    sf::CircleShape     m_vortex_center;
    sf::Font            m_font;
    sf::Text            m_statistics_text;
    sf::Time            m_statistics_update_time;
    sf::Time            m_pursuit_time;

    std::size_t         m_statistics_num_frames;
    bool                m_is_moving_up;
    bool                m_is_moving_down;
    bool                m_is_moving_left;
    bool                m_is_moving_right;

    float               m_estimated_time;
    sf::CircleShape     m_target;
    bool                m_game_is_over;
    sf::Text            m_game_over_text;
};

float           GetVectorLength(const sf::Vector2f& vec);
sf::Vector2f    GetNormalizedVector(const sf::Vector2f& vec);
sf::Vector2f    GetRotatedVector(
    const sf::Vector2f& vec,
    float angle
);
sf::Vector2f    GetRotatedAroundOriginVector(
    const sf::Vector2f& vec,
    const sf::Vector2f& origin,
    float angle
);
float           TimeFunction(
    float time,
    sf::Vector2f copter,
    sf::Vector2f cutter
);
