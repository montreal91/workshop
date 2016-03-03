
#ifndef __MULTIPLAYER_GAME_STATE_HPP__
#define __MULTIPLAYER_GAME_STATE_HPP__


#include "State.hpp"
#include "World.hpp"
#include "Player.hpp"
#include "GameServer.hpp"
#include "NetworkProtocol.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/Packet.hpp>


class MultiplayerGameState : public State {
public:
    // TODO: include StateStack.hpp
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
    TextureHolder&              mTextureHolder; // TODO: include ResourceHolders.hpp

    std::map<int, PlayerPtr>    mPlayers; // TODO: include map
    std::vector<sf::Int32>      mLocalPlayerIdentifiers;
    sf::TcpSocket               mSocket;
    bool                        mConnected;
    std::unique_ptr<GameServer> mGameServer;
    sf::Clock                   mTickClock;

    std::vector<std::string>    mBroadcasts; // TODO: include string
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

#endif // __MULTIPLAYER_GAME_STATE_HPP__
