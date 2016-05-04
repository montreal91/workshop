
#include "controller.h"


using namespace std::placeholders;

namespace ih {
struct EsBoxMover {
    EsBoxMover( float vx, float vy, int identifier ):
    velocity( vx, vy ),
    box_id( identifier ) {}

    void operator() ( ERealBox& box, sf::Time dt ) const {
        if ( box_id == box.GetIdentifier() ) {
            b2Vec2 dv;
            dv.x = velocity.x * box.GetMaxSpeed();
            dv.y = velocity.y * box.GetMaxSpeed();
            box.Accelerate( dv );
        }
    }
    b2Vec2 velocity;
    int box_id;
};

EController::EController( const EKeyBinding* binding, int id ) :
m_current_mission_status( MissionRunning ),
m_id( id ) {
    this->InitializeActions();

    for ( auto& pair : this->m_action_binding ) {
        pair.second.category = EeCategory::PlayerShip;
    }
}

void
EController::HandleEvent( const sf::Event& event, ECommandQueue& commands ) {
    if ( event.type == sf::Event::KeyPressed ) {
        Action_t action;
        commands.Push( this->m_action_binding[action] );
    }
}

void
EController::HandleRealtimeInput( ECommandQueue& commands ) {
    std::vector<Action_t> active_actions = this->m_key_binding->GetActiveRealtimeActions();
    for ( auto action : active_actions ) {
        commands.Push( this->m_action_binding[action] );
    }
}

void
EController::SetMissionStatus( EeMissionStatus status ) {
    this->m_current_mission_status = status;
}

EController::EeMissionStatus
EController::GetMissionStatus() const {
    return this->m_current_mission_status;
}

void
EController::InitializeActions() {
    this->m_action_binding[player_action::MoveForward].action = FDerivedAction<ERealBox> (
        EsBoxMover( -1, 0, this->m_id )
    );

    this->m_action_binding[player_action::MoveBackward].action = FDerivedAction<ERealBox> (
        EsBoxMover( +1, 0, this->m_id )
    );
}

} // namespace ih
