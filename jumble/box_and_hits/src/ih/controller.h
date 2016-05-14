
#pragma once

#include <algorithm>
#include <map>
#include <string>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>

#include "src/ih/command.h"
#include "src/ih/command_queue.h"
// #include "src/ih/key_binding.h"
#include "src/nodes/entity.h"
#include "src/nodes/scene_node.h"


// Input Handler
namespace ih {

class EController : private sf::NonCopyable {
public:
    // typedef player_action::EeType Action_t;

    enum EeMissionStatus {
        MissionRunning,
        MissionSuccess,
        MissionFailure,
    };

    enum EeAction {
        Accelerate,
        Decelerate,
        RotateClockwise,
        RotateCounterClockwise,        
    };

    EController();

    void                HandleEvent( const sf::Event& event, ECommandQueue& commands );
    void                HandleRealtimeInput( ECommandQueue& commands );
    void                SetMissionStatus( EeMissionStatus status );
    EeMissionStatus     GetMissionStatus() const;

    void                AssignKey( EeAction action, sf::Keyboard::Key key );
    sf::Keyboard::Key   GetAssignedKey( EeAction action ) const;

private:
    void            InitializeActions();
    static bool     IsRealtimeAction( EeAction action );

    std::map<sf::Keyboard::Key, EeAction>   m_key_binding;
    std::map<EeAction, EsCommand>           m_action_binding;

    EeMissionStatus                         m_current_mission_status;
};

} // namespace ih
