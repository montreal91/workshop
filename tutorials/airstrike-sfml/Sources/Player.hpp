
#pragma once


#include <map>
#include <string>
#include <algorithm>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/Packet.hpp>

#include "Aircraft.hpp"
#include "Command.hpp"
#include "CommandQueue.hpp"
#include "KeyBinding.hpp"
#include "NetworkProtocol.hpp"


class Player : private sf::NonCopyable {
public:
    typedef PlayerAction::Type Action;

    enum MissionStatus {
        MissionRunning,
        MissionSuccess,
        MissionFailure,
    };

    Player(
        sf::TcpSocket* socket,
        sf::Int32 identifier,
        const KeyBinding* binding
    );

    void                handleEvent(
        const sf::Event& event,
        CommandQueue& commands
    );
    void                handleRealtimeInput( CommandQueue& commands );
    void                handleRealtimeNetworkInput( CommandQueue& commands );

    // React to events of realtime state changes recieved over the network
    void                handleNetworkEvent(
        Action action, CommandQueue& commands
    );
    void                handleNetworkRealtimeChange(
        Action action, bool actionEnabled
    );

    void                setMissionStatus( MissionStatus status );
    MissionStatus       getMissionStatus() const;

    void                disableAllRealtimeActions();
    bool                isLocal() const;

private:
    void                                initalizeActions();

    const KeyBinding*                   mKeyBinding;
    std::map<Action, Command>           mActionBinding;
    std::map<Action, bool>              mActionProxies;
    MissionStatus                       mCurrentMissionStatus;
    int                                 mIdentifier;
    sf::TcpSocket*                      mSocket;
};
