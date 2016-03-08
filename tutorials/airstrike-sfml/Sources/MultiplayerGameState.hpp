
#pragma once

#include <fstream>
#include <map>
#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "GameServer.hpp"
#include "MusicPlayer.hpp"
#include "NetworkProtocol.hpp"
#include "Player.hpp"
#include "ResourceHolder.hpp"
#include "State.hpp"
#include "StateStack.hpp"
#include "Utility.hpp"
#include "World.hpp"


class MultiplayerGameState : public State {
public:
    MultiplayerGameState( StateStack& stak, Context context, bool isHost );

    virtual void    draw();
    virtual bool    update( sf::Time dt );
    virtual bool    handleEvent( const sf::Event& event );
    virtual void    onActivate();
    void            onDestroy();

    void            disableAllRealtimeActions();

private:
    void updateBroadcastMessage( sf::Time elapsedTime );
    void handlePacket( sf::Int32 packetType, sf::Packet& packet );

    typedef std::unique_ptr<Player> PlayerPtr;

    World                       mWorld;
    sf::RenderWindow&           mWindow;
    TextureHolder&              mTextureHolder;

    std::map<int, PlayerPtr>    mPlayers;
    std::vector<sf::Int32>      mLocalPlayerIdentifiers;
    sf::TcpSocket               mSocket;
    bool                        mConnected;
    std::unique_ptr<GameServer> mGameServer;
    sf::Clock                   mTickClock;

    std::vector<std::string>    mBroadcasts;
    sf::Text                    mBroadcastText;
    sf::Time                    mBroadcastElapsedTime;

    sf::Text                    mPlayerInvitationText;
    sf::Time                    mPlayerInvitationTime;

    sf::Text                    mFailedConnectionText;
    sf::Clock                   mFailedConnectionClock;

    bool                        mActiveState;
    bool                        mHasFocus;
    bool                        mHost;
    bool                        mGameStarted;
    sf::Time                    mClientTimeout;
    sf::Time                    mTimeSinceLastPacket;
};
