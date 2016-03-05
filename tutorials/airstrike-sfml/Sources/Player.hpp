
#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__


#include "Command.hpp"
#include "KeyBinding.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Network/TcpSocket.hpp>

#include <map>


// TODO: replace it with a proper import 
class CommandQueue;

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

#endif // __PLAYER_HPP__
