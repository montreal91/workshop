
#include "MultiplayerGameState.hpp"


sf::IpAddress
getAddressFromFile() {
    {
        // Try to open existing file (RAII block)
        std::ifstream   inputfile( "ip.txt" );
        std::string     ipAddress;
        if ( inputfile >> ipAddress ) return ipAddress;
    }
    std::ofstream   outputFile( "ip.txt" );
    std::string     localAddress = "127.0.0.1";
    outputFile << localAddress;
    return localAddress;
}

MultiplayerGameState::MultiplayerGameState(
    StateStack& stack, Context context, bool isHost ) :
State( stack, context ),
mWorld( *context.window, *context.fonts, *context.sounds, true ),
mWindow( *context.window ),
mTextureHolder( *context.textures ),
mConnected( false ),
mGameServer( nullptr ),
mActiveState( true ),
mHasFocus( true ),
mHost( isHost ),
mGameStarted( false ),
mClientTimeout( sf::seconds( 2.0f ) ),
mTimeSinceLastPacket( sf::seconds( 0.0f ) ) {
    mBroadcastText.setFont( context.fonts->get( Fonts::Main ) );
    mBroadcastText.setPosition( 1024.0f / 2, 100.0f );

    mPlayerInvitationText.setFont( context.fonts->get( Fonts::Main ) );
    mPlayerInvitationText.setCharacterSize( 20 );
    mPlayerInvitationText.setColor( sf::Color::White );
    mPlayerInvitationText.setString( "Press Enter to spawn player 2" );
    mPlayerInvitationText.setPosition(
        1000 - mPlayerInvitationText.getLocalBounds().width,
        760 - mPlayerInvitationText.getLocalBounds().height
    );

    // We reuse this text for "Attempt to connect"
    // and "Failed to connect" messages
    mFailedConnectionText.setFont( context.fonts->get( Fonts::Main ) );
    mFailedConnectionText.setString( "Attempting to connect..." );
    mFailedConnectionText.setCharacterSize( 35 );
    mFailedConnectionText.setColor( sf::Color::White );
    centerOrigin( mFailedConnectionText );
    mFailedConnectionText.setPosition(
        mWindow.getSize().x / 2.0f,
        mWindow.getSize().y / 2.0f
    );

    // Render a "establishing connection" frame for user feedback
    mWindow.clear( sf::Color::Black );
    mWindow.draw( mFailedConnectionText );
    mWindow.display();
    mFailedConnectionText.setString( "Could not connect to the remote server!" );
    centerOrigin( mFailedConnectionText );

    sf::IpAddress ip;
    if ( isHost ) {
        mGameServer.reset( new GameServer( sf::Vector2f( mWindow.getSize() ) ) );
        ip = "127.0.0.1";
    } else {
        ip = getAddressFromFile();
    }

    if ( mSocket.connect( ip, ServerPort, sf::seconds( 5.0f ) ) == sf::TcpSocket::Done ) {
        mConnected = true;
    } else {
        mFailedConnectionClock.restart();
    }

    mSocket.setBlocking( false );

    context.music->play( Music::MissionTheme );
}

void
MultiplayerGameState::draw() {
    if ( mConnected ) {
        mWorld.draw();

        // Broadcast messages in default view
        mWindow.setView( mWindow.getDefaultView() );

        if ( !mBroadcasts.empty() ) mWindow.draw( mBroadcastText );

        // TODO: wrap this condition in method
        if ( mLocalPlayerIdentifiers.size() < 2 && mPlayerInvitationTime < sf::seconds( 0.5f ) ) {
            mWindow.draw( mPlayerInvitationText );
        }
    } else {
        mWindow.draw( mFailedConnectionText );
    }
}

void
MultiplayerGameState::onActivate() {
    mActiveState = true;
}

void
MultiplayerGameState::onDestroy() {
    if ( !mHost && mConnected ) {
        // Inform server this client is dying
        sf::Packet packet;
        packet << static_cast<sf::Int32>( Client::Quit );
        mSocket.send( packet );
    }
}

bool
MultiplayerGameState::update( sf::Time dt ) {
    // Connected to server: Handle all the network logic
    if ( mConnected ) {
        mWorld.update( dt );

        // Remove players whose aircrafts were destroyed
        // TODO: outsource it to the separate method
        bool foundLocalPlane = false;
        for ( auto itr = mPlayers.begin(); itr != mPlayers.end(); ) {
            // Check if there are no more local planes for remote clients
            // TODO: outsource heavy condition to a method
            if ( std::find( mLocalPlayerIdentifiers.begin(), mLocalPlayerIdentifiers.end(), itr->first ) != mLocalPlayerIdentifiers.end() ) {
                foundLocalPlane = true;
            }

            if ( !mWorld.getAircraft( itr->first ) ) {
                itr = mPlayers.erase( itr );

                // No more players left: Mission failed
                if ( mPlayers.empty() ) requestStackPush( States::GameOver );
            } else {
                ++itr;
            }
        }

        if ( !foundLocalPlane && mGameStarted ) {
            requestStackPush( States::GameOver );
        }

        // Only handle the realtime input if the window has focus
        // and the game is unpaused
        if ( mActiveState && mHasFocus ) {
            CommandQueue& commands = mWorld.getCommandQueue();
            for ( auto& pair : mPlayers ) {
                pair.second->handleRealtimeInput( commands );
            }
        }

        // Always handle the network input
        // TODO: outsource it
        CommandQueue& commands = mWorld.getCommandQueue();
        for ( auto& pair : mPlayers ) {
            pair.second->handleRealtimeInput( commands );
        }

        // Handle messages from server that may have arrived
        // TODO: outsource it
        sf::Packet packet;
        if ( mSocket.receive( packet ) == sf::Socket::Done ) {
            mTimeSinceLastPacket = sf::seconds( 0.0f );
            sf::Int32 packetType;
            packet >> packetType;
            handlePacket( packetType, packet );
        } else {
            // Check for timeout with the server
            if ( mTimeSinceLastPacket > mClientTimeout ) {
                mConnected = false;

                mFailedConnectionText.setString( "Lost connection to server" );
                centerOrigin( mFailedConnectionText );

                mFailedConnectionClock.restart();
            }
        }
        updateBroadcastMessage( dt );

        // Time counter for blinking 2nd player text
        mPlayerInvitationTime += dt;
        if ( mPlayerInvitationTime > sf::seconds( 1.0f ) ) {
            mPlayerInvitationTime = sf::Time::Zero;
        }

        // Events occuring in the game
        GameActions::Action gameAction;
        while( mWorld.pollGameAction( gameAction ) ) {
            sf::Packet packet;
            packet << static_cast<sf::Int32>( Client::GameEvent );
            packet << static_cast<sf::Int32>( gameAction.type );
            packet << gameAction.position.x;
            packet << gameAction.position.y;

            mSocket.send( packet );
        }

        // Regular position updates
        if ( mTickClock.getElapsedTime() > sf::seconds( 1.0f / 20.0f ) ) {
            sf::Packet positionUpdatePacket;
            positionUpdatePacket << static_cast<sf::Int32>(
                Client::PositionUpdate
            );
            positionUpdatePacket << static_cast<sf::Int32>(
                mLocalPlayerIdentifiers.size()
            );

            for ( sf::Int32 identifier : mLocalPlayerIdentifiers ) {
                if ( Aircraft* aircraft = mWorld.getAircraft( identifier ) ) {
                    positionUpdatePacket << identifier;
                    positionUpdatePacket << aircraft->getPosition().x;
                    positionUpdatePacket << aircraft->getPosition().y;
                    positionUpdatePacket << static_cast<sf::Int32>(
                        aircraft->GetHitpoints()
                    );
                    positionUpdatePacket << static_cast<sf::Int32>(
                        aircraft->GetMissileAmmo()
                    );
                }
            }
            mSocket.send( positionUpdatePacket );
            mTickClock.restart();
        }
        mTimeSinceLastPacket += dt;
    } else if ( mFailedConnectionClock.getElapsedTime() >= sf::seconds( 5.0f ) ) {
        requestStateClear();
        requestStackPush( States::Menu );
    }
    return true;
}

void
MultiplayerGameState::disableAllRealtimeActions() {
    mActiveState = false;

    for ( sf::Int32 identifier : mLocalPlayerIdentifiers ) {
        mPlayers[identifier]->disableAllRealtimeActions();
    }
}

bool
MultiplayerGameState::handleEvent( const sf::Event& event ) {
    CommandQueue& commands = mWorld.getCommandQueue();

    // Forward event to all players
    for ( auto& pair : mPlayers ) {
        pair.second->handleEvent( event, commands );
    }

    if ( event.type == sf::Event::KeyPressed ) {
        if ( event.key.code == sf::Keyboard::Return && mLocalPlayerIdentifiers.size() == 1 ) {
            sf::Packet packet;
            packet << static_cast<sf::Int32>( Client::RequestCoopPartner );
            mSocket.send( packet );
        } else if ( event.key.code == sf::Keyboard::Escape ) {
            disableAllRealtimeActions();
            requestStackPush( States::NetworkPause );
        }
    } else if ( event.type == sf::Event::GainedFocus ) {
        mHasFocus = true;
    } else if ( event.type == sf::Event::LostFocus ) {
        mHasFocus = false;
    }
    return true;
}

void
MultiplayerGameState::updateBroadcastMessage( sf::Time elapsedTime ) {
    if ( mBroadcasts.empty() ) return;

    mBroadcastElapsedTime += elapsedTime;
    if ( mBroadcastElapsedTime > sf::seconds( 2.5f ) ) {
        mBroadcasts.erase( mBroadcasts.begin() );

        // Continue to display next broadcast message
        if ( !mBroadcasts.empty() ) {
            mBroadcastText.setString( mBroadcasts.front() );
            centerOrigin( mBroadcastText );
            mBroadcastElapsedTime = sf::Time::Zero;
        }
    }
}

// TODO: split this huge method into smaller ones
void
MultiplayerGameState::handlePacket( sf::Int32 packetType, sf::Packet& packet ) {
    switch ( packetType ) {
        case Server::BroadcastMessage: {
            std::string message;
            packet >> message;
            mBroadcasts.push_back( message );

            // Just added first message, display immediately
            if ( mBroadcasts.size() == 1 ) {
                mBroadcastText.setString( mBroadcasts.front() );
                centerOrigin( mBroadcastText );
                mBroadcastElapsedTime = sf::Time::Zero;
            }
        } break;
        case Server::SpawnSelf: {
            sf::Int32       aircraftIdentifier;
            sf::Vector2f    aircraftPosition;
            packet >> aircraftIdentifier;
            packet >> aircraftPosition.x >> aircraftPosition.y;

            Aircraft* aircraft = mWorld.addAircraft( aircraftIdentifier );
            aircraft->setPosition( aircraftPosition );

            mPlayers[aircraftIdentifier].reset(
                new Player( &mSocket, aircraftIdentifier, getContext().keys1 )
            );
            mLocalPlayerIdentifiers.push_back( aircraftIdentifier );

            mGameStarted = true;
        } break;
        case Server::PlayerConnect: {
            sf::Int32       aircraftIdentifier;
            sf::Vector2f    aircraftPosition;
            packet >> aircraftIdentifier;
            packet >> aircraftPosition.x >> aircraftPosition.y;

            Aircraft* aircraft = mWorld.addAircraft( aircraftIdentifier );
            aircraft->setPosition( aircraftPosition );

            mPlayers[aircraftIdentifier].reset(
                new Player( &mSocket, aircraftIdentifier, nullptr )
            );
        } break;
        case Server::PlayerDisconnect: {
            sf::Int32 aircraftIdentifier;
            packet >> aircraftIdentifier;

            mWorld.removeAircraft( aircraftIdentifier );
            mPlayers.erase( aircraftIdentifier );
        } break;
        case Server::InitialState: {
            float worldHeight, currentScroll;
            packet >> worldHeight >> currentScroll;

            mWorld.setWorldHeight( worldHeight );
            mWorld.setCurrentBattleFieldPosition( currentScroll );

            sf::Int32 aircraftCount;
            packet >> aircraftCount;

            for ( sf::Int32 i=0; i<aircraftCount; i++ ) {
                sf::Int32       aircraftIdentifier;
                sf::Int32       hitpoints;
                sf::Int32       missileAmmo;
                sf::Vector2f    aircraftPosition;
                packet >> aircraftIdentifier;
                packet >> aircraftPosition.x >> aircraftPosition.y;
                packet >> hitpoints >> missileAmmo;

                Aircraft* aircraft = mWorld.addAircraft( aircraftIdentifier );
                aircraft->setPosition( aircraftPosition );
                aircraft->SetHitpoints( hitpoints );
                aircraft->SetMissileAmmo( missileAmmo );

                mPlayers[aircraftIdentifier].reset(
                    new Player( &mSocket, aircraftIdentifier, nullptr )
                );
            }
        } break;
        case Server::AcceptCoopPartner: {
            sf::Int32 aircraftIdentifier;
            packet >> aircraftIdentifier;

            mWorld.addAircraft( aircraftIdentifier );
            mPlayers[aircraftIdentifier].reset(
                new Player( &mSocket, aircraftIdentifier, getContext().keys2 )
            );
            mLocalPlayerIdentifiers.push_back( aircraftIdentifier );
        } break;
        case Server::PlayerEvent: {
            sf::Int32 aircraftIdentifier;
            sf::Int32 action;
            packet >> aircraftIdentifier >> action;

            auto itr = mPlayers.find( aircraftIdentifier );
            if ( itr != mPlayers.end() ) {
                itr->second->handleNetworkEvent(
                    static_cast<Player::Action>( action ),
                    mWorld.getCommandQueue()
                );
            }
        } break;
        case Server::PlayerRealtimeChange: {
            sf::Int32   aircraftIdentifier;
            sf::Int32   action;
            bool        actionEnabled;
            packet >> aircraftIdentifier >> action >> actionEnabled;

            auto itr = mPlayers.find( aircraftIdentifier );
            if ( itr != mPlayers.end() ) {
                itr->second->handleNetworkRealtimeChange(
                    static_cast<Player::Action>( action ),
                    actionEnabled
                );
            }
        } break;
        case Server::SpawnEnemy: {
            float       height;
            sf::Int32   type;
            float       relativeX;
            packet >> type >> height >> relativeX;

            mWorld.addEnemy(
                static_cast<Aircraft::Type>( type ),
                relativeX,
                height
            );
            mWorld.sortEnemies();
        } break;
        case Server::MissionSuccess: {
            requestStackPush( States::MissionSuccess );
        } break;
        case Server::SpawnPickup: {
            sf::Int32       type;
            sf::Vector2f    position;
            packet >> type >> position.x >> position.y;

            mWorld.createPickup( position, static_cast<Pickup::Type>( type ) );
        } break;
        case Server::UpdateClientState: {
            float       currentWorldPosition;
            sf::Int32   aircraftCount;
            packet >> currentWorldPosition >> aircraftCount;

            float currentViewPosition = mWorld.getViewBounds().top + mWorld.getViewBounds().height;

            mWorld.setWorldScrollCompensation(
                currentViewPosition / currentWorldPosition
            );

            for ( sf::Int32 i=0; i<aircraftCount; i++ ) {
                sf::Vector2f    aircraftPosition;
                sf::Int32       aircraftIdentifier;
                packet >> aircraftIdentifier;
                packet >> aircraftPosition.x >> aircraftPosition.y;

                Aircraft* aircraft = mWorld.getAircraft( aircraftIdentifier );
                bool isLocalPlane = std::find(
                    mLocalPlayerIdentifiers.begin(),
                    mLocalPlayerIdentifiers.end(),
                    aircraftIdentifier) != mLocalPlayerIdentifiers.end();
                if ( aircraft && !isLocalPlane ) {
                    sf::Vector2f interpolatedPosition = aircraft->getPosition() + (
                        aircraftPosition - aircraft->getPosition() ) * 0.1f;
                    aircraft->setPosition( interpolatedPosition );
                }
            }
        } break;
    }
}
