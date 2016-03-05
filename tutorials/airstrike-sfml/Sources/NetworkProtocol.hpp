
#ifndef __NETWORK_PROTOCOL_HPP__
#define __NETWORK_PROTOCOL_HPP__


#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>


const unsigned short ServerPort = 5000;

namespace Server {
// Packets originated in the server
enum PacketType {
    BroadcastMessage,   // format: [Int32:packetType][string:message]
    SpawnSelf,          // format: [Int32:packetType]
    InitialState,
    PlayerEvent,
    PlayerRealtimeChange,
    PlayerConnect,
    PlayerDisconnect,
    AcceptCoopPartner,
    SpawnEnemy,
    SpawnPickup,
    UpdateClientState,
    MissionSuccess,
};
} // namespace Server

namespace Client {
// Packets originated in the client
enum PacketType {
    PlayerEvent,
    PlayerRealtimeChange,
    RequestCoopPartner,
    PositionUpdate,
    GameEvent,
    Quit,
};
} // namespace Client

namespace PlayerActions {
enum Action {
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    Fire,
    LaunchMissile,
    ActionCount,
};
} // namespace PlayerActions

namespace GameActions {
enum Type {
    EnemyExplode,
};

struct Action {
    Action() {} // Leave uninitalized
    Action( Type type, sf::Vector2f position ) :
    type( type ),
    position( position ) {}

    Type            type;
    sf::Vector2f    position;
};
} // namespace GameActions

#endif // __NETWORK_PROTOCOL_HPP__
