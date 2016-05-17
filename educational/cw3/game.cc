
#include "game.h"


const float CwGame::PLAYER_SPEED        = 100.0f;
const float CwGame::COPTER_SPEED        = 200.0f;
const float CwGame::VORTEX_ANGULAR_SPEED = M_PI / 5.5;
const sf::Vector2f CwGame::VORTEX_CENTER = sf::Vector2f( 400.0f, 300.0f );
const sf::Time CwGame::TIME_PER_FRAME   = sf::seconds( 1.0f / 60.0f );

CwGame::CwGame() :
m_window( sf::VideoMode( 800, 600 ), "CUTTER & COPTER", sf::Style::Close ),
m_player( 20.0f ),
m_copter( 40.0f ),
m_is_moving_up( false ),
m_is_moving_down( false ),
m_is_moving_left( false ),
m_is_moving_right( false ) {
    this->m_player.setPosition( 000.0f, 100.0f );
    this->m_player.setFillColor( sf::Color( 10, 120, 10 ) );
    this->m_copter.setFillColor( sf::Color( 120, 10, 10 ) );
}

void
CwGame::Run() {
    sf::Clock clock;
    sf::Time time_since_last_update = sf::Time::Zero;
    while ( this->m_window.isOpen() ) {
        sf::Time elapsed_time = clock.restart();
        time_since_last_update += elapsed_time;
        if ( time_since_last_update >= TIME_PER_FRAME ) {
            this->ProcessEvents();
            this->Update( TIME_PER_FRAME );
            this->Render();
            time_since_last_update = sf::Time::Zero;
        }
    }
}

void
CwGame::ProcessEvents() {
    sf::Event event;
    while ( this->m_window.pollEvent( event ) ) {
        switch ( event.type ) {
            case sf::Event::KeyPressed:
                this->HandlePlayerInput( event.key.code, true );
                break;
            case sf::Event::KeyReleased:
                this->HandlePlayerInput( event.key.code, false );
                break;
            case sf::Event::Closed:
                this->m_window.close();
                break;
        }
    }
}

void
CwGame::ApplyVortexRotation( const sf::Time& dt ) {
    sf::Vector2f rotation_radius = this->m_player.getPosition() - VORTEX_CENTER;
    float len = std::sqrt(
        pow( rotation_radius.x, 2 ) + pow( rotation_radius.y, 2 )
    );
    this->NormalizeVector( &rotation_radius );
    float angle = VORTEX_ANGULAR_SPEED * dt.asSeconds();
    float cos_phi = rotation_radius.x;
    float sin_phi = rotation_radius.y;
    rotation_radius.x = len * ( cos_phi * std::cos( angle ) - sin_phi * std::sin( angle ) );
    rotation_radius.y = len * ( sin_phi * std::cos( angle ) + cos_phi * std::sin( angle ) );
    this->m_player.setPosition( VORTEX_CENTER + rotation_radius );
}

void
CwGame::GuideCopter( const sf::Time& dt ) {
    sf::Vector2f player_pos = this->m_player.getPosition();
    sf::Vector2f velocity = player_pos - this->m_copter.getPosition();
    this->NormalizeVector( &velocity );
    this->m_copter.move( velocity * COPTER_SPEED * dt.asSeconds() );
}

void
CwGame::Update( const sf::Time& dt ) {
    this->ApplyVortexRotation( dt );

    sf::Vector2f velocity( 0.0f, 0.0f );
    if ( this->m_is_moving_up ) velocity.y -= 10;
    if ( this->m_is_moving_down ) velocity.y += 10;
    if ( this->m_is_moving_left ) velocity.x -= 10;
    if ( this->m_is_moving_right ) velocity.x += 10;

    this->NormalizeVector( &velocity );
    this->m_player.move( velocity * PLAYER_SPEED * dt.asSeconds() );

    this->GuideCopter( dt );
}

void
CwGame::Render() {
    this->m_window.clear();
    this->m_window.draw( this->m_player );
    this->m_window.draw( this->m_copter );
    this->m_window.display();
}

void
CwGame::HandlePlayerInput( sf::Keyboard::Key key, bool is_pressed ) {
    if ( key == sf::Keyboard::W ) {
        this->m_is_moving_up = is_pressed;
    } else if ( key == sf::Keyboard::S ) {
        this->m_is_moving_down = is_pressed;
    } else if ( key == sf::Keyboard::A ) {
        this->m_is_moving_left = is_pressed;
    } else if ( key == sf::Keyboard::D ) {
        this->m_is_moving_right = is_pressed;
    }
}

void
CwGame::NormalizeVector( sf::Vector2f* vec ) const {
    float len = std::sqrt( vec->x * vec->x + vec->y * vec->y );
    if ( fabs( len ) >= 0.00000001 ) {
        vec->x = vec->x / len;
        vec->y = vec->y / len;
    }
}

sf::Vector2f
CwGame::GetOrthogonalVector( const sf::Vector2f& vec ) const {
    sf::Vector2f res;
    res.x = 1;
    res.y = vec.x / vec.y;
    this->NormalizeVector( &res );
    return res;
}
