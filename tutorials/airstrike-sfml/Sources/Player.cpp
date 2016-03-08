
#include "Player.hpp"


using namespace std::placeholders;

struct AircraftMover {
    AircraftMover( float vx, float vy, int identifier ):
    velocity( vx, vy ),
    aircraftID( identifier ) {}
    
    void operator() ( Aircraft& aircraft, sf::Time dt ) const {
        if ( aircraft.getIdentifier() == aircraftID ) {
            aircraft.accelerate( velocity * aircraft.getMaxSpeed() );
        }
    }

    sf::Vector2f    velocity;
    int             aircraftID;
};

struct AircraftFireTrigger {
    AircraftFireTrigger( int identifier ) :
    aircraftID( identifier ) {}

    void operator() ( Aircraft& aircraft, sf::Time ) const {
        if ( aircraft.getIdentifier() == aircraftID ) {
            aircraft.fire();
        }
    }
    int aircraftID;
};

struct AircraftMissileTrigger {
    AircraftMissileTrigger( int identifier ) :
    aircraftID( identifier ) {}

    void operator() ( Aircraft& aircraft, sf::Time ) const {
        if ( aircraft.getIdentifier() == aircraftID ) {
            aircraft.launchMissile();
        }
    }
    int aircraftID;
};

Player::Player(
    sf::TcpSocket* socket,
    sf::Int32 identifier,
    const KeyBinding* binding
) : mKeyBinding( binding ),
mCurrentMissionStatus( MissionRunning ),
mIdentifier( identifier ),
mSocket( socket ) {
    initalizeActions();

    for( auto& pair : mActionBinding ) {
        pair.second.category = Category::PlayerAircraft;
    }
}

void
Player::handleEvent( const sf::Event& event, CommandQueue& commands ) {
    if ( event.type == sf::Event::KeyPressed ) {
        Action action;
        // TODO: put this complex condition into function
        if ( mKeyBinding && mKeyBinding->checkAction( event.key.code, action ) && !isRealtimeAction( action ) ) {
            if ( mSocket ) {
                // Network game
                sf::Packet packet;
                packet << static_cast<sf::Int32>( Client::PlayerEvent );
                packet << mIdentifier;
                packet << static_cast<sf::Int32>( action );
                mSocket->send( packet );
            } else {
                // Local game
                commands.push( mActionBinding[action] );
            }
        }
    }
    // Realtime change (network connected)
    // TODO: put it into function
    if ( ( event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased ) && mSocket ) {
        Action action;
        if ( mKeyBinding && mKeyBinding->checkAction( event.key.code, action ) && isRealtimeAction( action ) ) {
            sf::Packet packet;
            packet << static_cast<sf::Int32>( Client::PlayerRealtimeChange );
            packet << mIdentifier;
            packet << static_cast<sf::Int32>( action );
            packet << ( event.type == sf::Event::KeyPressed );
            mSocket->send( packet );
        }
    }
}

bool
Player::isLocal() const {
    // No key binding means this player is remote
    return mKeyBinding != nullptr;
}

void
Player::disableAllRealtimeActions() {
    for ( auto& action : mActionProxies ) {
        sf::Packet packet;
        packet << static_cast<sf::Int32>( Client::PlayerRealtimeChange );
        packet << mIdentifier;
        packet << static_cast<sf::Int32>( action.first );
        packet << false;
        mSocket->send( packet );
    }
}

void
Player::handleRealtimeInput( CommandQueue& commands ) {
    // Check if this is a networked game and local player or just
    // a single player game.
    if ( ( mSocket && isLocal() ) || !mSocket ) {
        // Lookup all actions and push corresponding commands to queue
        std::vector<Action> activeActions = mKeyBinding->getRealtimeActions();
        for ( Action action : activeActions ) {
            commands.push( mActionBinding[action] );
        }
    }
}

void Player::handleRealtimeNetworkInput( CommandQueue& commands ) {
    if ( mSocket && !isLocal() ) {
        // Traverse all realtime input proxies.
        // Because this is a networked game, input isn't handled directly
        for ( auto pair : mActionProxies ) {
            if ( pair.second && isRealtimeAction( pair.first ) ) {
                commands.push( mActionBinding[pair.first] );
            }
        }
    }
}

void
Player::handleNetworkEvent( Action action, CommandQueue& commands ) {
    commands.push( mActionBinding[action] );
}

void
Player::handleNetworkRealtimeChange( Action action, bool actionEnabled ) {
    mActionProxies[action] = actionEnabled;
}

void
Player::setMissionStatus( MissionStatus status ) {
    mCurrentMissionStatus = status;
}

Player::MissionStatus
Player::getMissionStatus() const {
    return mCurrentMissionStatus;
}

void
Player::initalizeActions() {
    mActionBinding[PlayerAction::MoveLeft].action         = derivedAction<Aircraft>(
        AircraftMover( -1, 0, mIdentifier )
    );
    mActionBinding[PlayerAction::MoveRight].action = derivedAction<Aircraft>(
        AircraftMover( +1, 0, mIdentifier )
    );
    mActionBinding[PlayerAction::MoveUp].action = derivedAction<Aircraft>(
        AircraftMover( 0, -1, mIdentifier )
    );
    mActionBinding[PlayerAction::MoveDown].action = derivedAction<Aircraft>(
        AircraftMover( 0, +1, mIdentifier )
    );
    mActionBinding[PlayerAction::Fire].action = derivedAction<Aircraft>(
        AircraftFireTrigger( mIdentifier )
    );
    mActionBinding[PlayerAction::LaunchMissile].action = derivedAction<Aircraft>(
        AircraftMissileTrigger( mIdentifier )
    );
}
