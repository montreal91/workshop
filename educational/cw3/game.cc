
#include "game.h"


const float CwGame::PLAYER_SPEED            = 50.0f;
const float CwGame::COPTER_SPEED            = 100.0f;
const float CwGame::VORTEX_ANGULAR_SPEED    = M_PI / 12.0f;
const sf::Vector2f CwGame::VORTEX_CENTER    = sf::Vector2f(
    500.0f, 300.0f
);
const sf::Time CwGame::TIME_PER_FRAME       = sf::seconds(
    1.0f / 60.0f
);

CwGame::CwGame() :
m_window(
    sf::VideoMode(1000, 600),
    "CUTTER & COPTER",
    sf::Style::Close
),
m_player(5.0f),
m_copter(10.0f),
m_vortex_center(4.0f),
m_font(),
m_statistics_text(),
m_statistics_update_time(),
m_pursuit_time(),
m_statistics_num_frames(0),
m_is_moving_up(false),
m_is_moving_down(false),
m_is_moving_left(false),
m_is_moving_right(false),
m_estimated_time(0.0f),
m_target(2.0f),
m_game_is_over(false),
m_game_over_text() {
    this->m_player.setPosition(
        VORTEX_CENTER + sf::Vector2f(0.0f, 100.0f)
    );
    this->m_vortex_center.setPosition(
        VORTEX_CENTER - sf::Vector2f(2.0f, 2.0f)
    );
    this->m_player.setFillColor(sf::Color(10, 120, 10));
    this->m_copter.setFillColor(sf::Color(120, 10, 10));
    this->m_vortex_center.setFillColor(sf::Color(10, 10, 120));

    this->m_target.setFillColor(sf::Color(120, 120, 10));

    sf::Vector2f player_pos = this->m_player.getPosition() - VORTEX_CENTER;
    sf::Vector2f copter_pos = this->m_copter.getPosition() - VORTEX_CENTER;

    CwZeroFinder::CwRealFunction_t fun = TimeFunction;
    CwZeroFinder finder(fun, copter_pos, player_pos);
    float estimated_time        = finder.GetZero();
    this->m_estimated_time      = estimated_time;

    this->m_font.loadFromFile("DroidSansMono.ttf");
    this->m_statistics_text.setFont( this->m_font );
    this->m_statistics_text.setPosition( 5.0f, 5.0f );
    this->m_statistics_text.setCharacterSize( 15 );

    this->m_game_over_text.setFont( this->m_font );
    this->m_game_over_text.setPosition( 400.0f, 300.0f );
    this->m_game_over_text.setCharacterSize( 25 );
}

void
CwGame::Run() {
    sf::Clock clock;
    sf::Time time_since_last_update = sf::Time::Zero;
    while (this->m_window.isOpen()) {
        sf::Time elapsed_time = clock.restart();
        time_since_last_update += elapsed_time;
        while (time_since_last_update > TIME_PER_FRAME) {
            time_since_last_update -= TIME_PER_FRAME;
            this->ProcessEvents();
            this->Update(TIME_PER_FRAME);
        }
        this->UpdateStatistics(elapsed_time);
        this->Render();
    }
}

void
CwGame::ProcessEvents() {
    sf::Event event;
    while (this->m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                this->HandlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                this->HandlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                this->m_window.close();
                break;
        }
    }
}

void
CwGame::ApplyVortexRotation(const sf::Time& dt) {
    sf::Vector2f rot_radius = this->m_player.getPosition() - VORTEX_CENTER;
    float len           = GetVectorLength(rot_radius);
    this->NormalizeVector(&rot_radius);
    float angle         = VORTEX_ANGULAR_SPEED * dt.asSeconds();
    float cos_phi       = rot_radius.x;
    float sin_phi       = rot_radius.y;
    rot_radius.x        = len * (
        cos_phi * std::cos(angle) - sin_phi * std::sin(angle)
    );
    rot_radius.y        = len * (
        sin_phi * std::cos(angle) + cos_phi * std::sin(angle)
    );
    this->m_player.setPosition(VORTEX_CENTER + rot_radius);
}

void
CwGame::GuideCopter(const sf::Time& dt) {
    auto rotated_vector = GetRotatedAroundOriginVector(
        this->m_player.getPosition(),
        VORTEX_CENTER,
        VORTEX_ANGULAR_SPEED * (this->m_estimated_time - this->m_pursuit_time.asSeconds())
    );
    this->m_target.setPosition(rotated_vector);

    sf::Vector2f vcity          = rotated_vector - this->m_copter.getPosition();
    this->NormalizeVector(&vcity);
    this->m_copter.move(vcity * COPTER_SPEED * dt.asSeconds());
}

void
CwGame::Update(const sf::Time& dt) {
    sf::Vector2f distance = this->m_player.getPosition() - this->m_copter.getPosition();
    if (GetVectorLength(distance) < 3) {
        this->m_game_is_over = true;
    }
    if (!this->m_game_is_over) {
        this->ApplyVortexRotation(dt);

        sf::Vector2f vcity(0.0f, 0.0f);
        if (this->m_is_moving_up) vcity.y -= 10;
        if (this->m_is_moving_down) vcity.y += 10;
        if (this->m_is_moving_left) vcity.x -= 10;
        if (this->m_is_moving_right) vcity.x += 10;

        this->NormalizeVector(&vcity);
        this->m_player.move(vcity * PLAYER_SPEED * dt.asSeconds());

        this->GuideCopter(dt);
    }
}

void
CwGame::Render() {
    this->m_window.clear();
    if (!this->m_game_is_over) {
        this->m_window.draw(this->m_copter);
        this->m_window.draw(this->m_player);
        this->m_window.draw(this->m_vortex_center);
        this->m_window.draw(this->m_target);
        this->m_window.draw(this->m_statistics_text);
    } else {
        this->m_game_over_text.setString("Pursuit is over");
        this->m_window.draw(this->m_game_over_text);
    }
    this->m_window.display();
}

void
CwGame::UpdateStatistics( const sf::Time& dt ) {
    this->m_statistics_update_time += dt;
    this->m_statistics_num_frames += 1;
    this->m_pursuit_time += dt;
    if (this->m_statistics_update_time >= sf::seconds(1.0f)) {
        std::string result_string;
        result_string += "FPS           : ";
        result_string += std::to_string(
            this->m_statistics_num_frames
        );
        result_string += "\nTime / Update : ";
        float ut = m_statistics_update_time.asMicroseconds();
        result_string += std::to_string(
            ut / this->m_statistics_num_frames
        );
        result_string += "us\n";
        result_string += "Pursuit time  : ";
        result_string += std::to_string(
            this->m_pursuit_time.asSeconds()
        );
        result_string += " s.\n";
        result_string += "Estimated time: ";
        result_string += std::to_string(this->m_estimated_time);
        this->m_statistics_text.setString(result_string);
        this->m_statistics_update_time -= sf::seconds(1.0f);
        this->m_statistics_num_frames = 0;
    }
}

void
CwGame::HandlePlayerInput(sf::Keyboard::Key key, bool pressed) {
    if (key == sf::Keyboard::W) {
        this->m_is_moving_up = pressed;
    } else if (key == sf::Keyboard::S) {
        this->m_is_moving_down = pressed;
    } else if (key == sf::Keyboard::A) {
        this->m_is_moving_left = pressed;
    } else if (key == sf::Keyboard::D) {
        this->m_is_moving_right = pressed;
    }
}

void
CwGame::NormalizeVector(sf::Vector2f* vec) const {
    float len = std::sqrt( vec->x * vec->x + vec->y * vec->y );
    if (fabs(len) >= 0.00000001) {
        vec->x = vec->x / len;
        vec->y = vec->y / len;
    }
}

float
GetVectorLength(const sf::Vector2f& vec) {
    float sqr_length = std::pow(vec.x, 2) + std::pow(vec.y, 2);
    return std::sqrt(sqr_length);
}

sf::Vector2f
GetNormalizedVector(const sf::Vector2f& vec) {
    float len = GetVectorLength(vec);
    if (len >= 0.00001f) {
        return vec / GetVectorLength(vec);
    } else {
        return sf::Vector2f();
    }
}

sf::Vector2f
GetRotatedVector(
    const sf::Vector2f& vec,
    float angle
) {
    sf::Vector2f res;
    res.x = vec.x * std::cos(angle) - vec.y * std::sin(angle);
    res.y = vec.y * std::cos(angle) + vec.x * std::sin(angle);
    return res;
}

sf::Vector2f
GetRotatedAroundOriginVector(
    const sf::Vector2f& vec,
    const sf::Vector2f& origin,
    float angle
) {
    auto radius = vec - origin;
    auto rotated_vector = GetRotatedVector(radius, angle);
    return rotated_vector + origin;
}

float
TimeFunction(
    float time,
    sf::Vector2f copter,
    sf::Vector2f cutter
) {
    sf::Vector2f cutter_n   = GetNormalizedVector(cutter);
    sf::Vector2f copter_n   = GetNormalizedVector(copter);
    float cutter_len        = GetVectorLength(cutter);
    float copter_len        = GetVectorLength(copter);

    float first             = std::cos(
        CwGame::VORTEX_ANGULAR_SPEED * time
    ) * copter_n.x;
    float second            = std::sin(
        CwGame::VORTEX_ANGULAR_SPEED * time
    ) * copter_n.y;
    float third             = (first - second) * cutter_n.x;

    float fourth            = std::sin(
        CwGame::VORTEX_ANGULAR_SPEED * time
    ) * copter_n.x;
    float fith              = std::cos(
        CwGame::VORTEX_ANGULAR_SPEED * time
    ) * copter_n.y;
    float sixth             = ( fourth + fith ) * cutter_n.y;

    float cosine            = third + sixth;

    float root1             = std::pow(cutter_len, 2) + std::pow(copter_len, 2);
    float root2             = 2 * cutter_len * copter_len * cosine;

    return std::sqrt(root1 - root2) - (CwGame::COPTER_SPEED - CwGame::PLAYER_SPEED) * time;
}
