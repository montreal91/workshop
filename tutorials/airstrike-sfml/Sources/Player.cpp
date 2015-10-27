
#include "Player.hpp"
#include "CommandQueue.hpp"
#include "Aircraft.hpp"

#include <map>
#include <string>
#include <algorithm>

struct AircraftMover {
    AircraftMover( float vx, float vy ):
    velocity( vx, vy ) {
    }
    
    void operator() ( Aircraft& aircraft, sf::Time dt ) const {
        aircraft.accelerate( velocity );
    }

    sf::Vector2f velocity;
};

Player::Player() {
    mKeyBinding[ sf::Keyboard::Left] = MoveLeft;
    mKeyBinding[sf::Keyboard::Right] = MoveRight;
    mKeyBinding[ sf::Keyboard::Up ] = MoveUp;
    mKeyBinding[ sf::Keyboard::Down] = MoveDown;

    initalizeActions();

    for( auto& pair : mActionBinding ) {
        pair.second.category = Category::PlayerAircraft;
    }
}

void
Player::handleEvent( const sf::Event& event, CommandQueue& commands ) {
    if ( event.type == sf::Event::KeyPressed ) {
        auto found = mKeyBinding.find( event.key.code );
        if ( found != mKeyBinding.end() && !isRealtimeAction( found->second ) ) {
            commands.push( mActionBinding[found->second] );
        }
    }
}

void
Player::handleRealtimeInput( CommandQueue& commands ) {
    for( auto pair : mKeyBinding ) {
        if ( sf::Keyboard::isKeyPressed( pair.first ) && isRealtimeAction( pair.second ) ) {
            commands.push( mActionBinding[ pair.second ] );
        }
    }
}

void
Player::assignKey( Action action, sf::Keyboard::Key key ) {
    for ( auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); ) {
        if ( itr->second == action ) {
            mKeyBinding.erase( itr++ );
        } else {
            itr++;
        }
    }
    mKeyBinding[ key] = action;
}

sf::Keyboard::Key
Player::getAssignedKey( Action action ) const {
    for ( auto pair : mKeyBinding ) {
        if ( pair.second == action ) {
            return pair.first;
        }
    }
    return sf::Keyboard::Unknown;
}

void
Player::initalizeActions() {
    const float playerSpeed = 200.0f;

    mActionBinding[MoveLeft].action     = derivedAction<Aircraft>( AircraftMover( -playerSpeed, 0.0f ) );
    mActionBinding[MoveRight].action    = derivedAction<Aircraft>( AircraftMover( +playerSpeed, 0.0f ) );
    mActionBinding[MoveUp].action       = derivedAction<Aircraft>( AircraftMover( 0.0f, -playerSpeed ) );
    mActionBinding[MoveDown].action     = derivedAction<Aircraft>( AircraftMover( 0.0f, +playerSpeed ) );
}

bool
Player::isRealtimeAction( Action action ) {
    switch ( action ) {
        case MoveLeft:
        case MoveRight:
        case MoveUp:
        case MoveDown:
            return true;
        default:
            return false;
    }
}
