
#pragma once

#include <algorithm>
#include <map>
#include <string>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>

#include "src/ih/command.h"
#include "src/ih/command_queue.h"
#include "src/ih/key_binding.h"
#include "src/nodes/real_box.h"
#include "src/nodes/scene_node.h"


namespace ih {

class EController : private sf::NonCopyable {
public:
    typedef player_action::EeType Action_t;

    enum EeMissionStatus {
        MissionRunning,
        MissionSuccess,
        MissionFailure,
    };

    EController( const EKeyBinding* binding, int id );

    void                HandleEvent( const sf::Event& event, ECommandQueue& commands );
    void                HandleRealtimeInput( ECommandQueue& commands );
    void                SetMissionStatus( EeMissionStatus status );
    EeMissionStatus     GetMissionStatus() const;

private:
    void InitializeActions();

    const EKeyBinding*              m_key_binding;
    std::map<Action_t, EsCommand>   m_action_binding;
    std::map<Action_t, bool>        m_action_proxies;
    EeMissionStatus                 m_current_mission_status;
    int                             m_id;
};

} // namespace ih
