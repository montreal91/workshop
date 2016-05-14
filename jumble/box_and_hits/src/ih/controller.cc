
#include "controller.h"


namespace ih {
struct EsBoxMover {
    EsBoxMover( float vx, float vy ):
    velocity( vx, vy ) {}

    void operator() ( nodes::EEntity& box, sf::Time dt ) const {
        box.Accelerate( velocity );
    }
    b2Vec2 velocity;
};

EController::EController() :
m_current_mission_status( MissionRunning ) {
    this->m_key_binding[sf::Keyboard::Up] = Accelerate;
    this->m_key_binding[sf::Keyboard::Down] = Decelerate;
    this->InitializeActions();

    for ( auto& pair : this->m_action_binding ) {
        pair.second.category = EeCategory::PlayerShip;
    }
}

void
EController::HandleEvent( const sf::Event& event, ECommandQueue& commands ) {
    if ( event.type == sf::Event::KeyPressed ) {
        auto found = this->m_key_binding.find( event.key.code );
        if ( found != this->m_key_binding.end() && !IsRealtimeAction( found->second ) ) {
            commands.Push( this->m_action_binding[found->second]);
        }
    }
}

void
EController::HandleRealtimeInput( ECommandQueue& commands ) {
    for ( auto pair : this->m_key_binding ) {
        if ( sf::Keyboard::isKeyPressed( pair.first ) && IsRealtimeAction( pair.second ) ) {
            commands.Push( this->m_action_binding[pair.second] );
        }
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
EController::AssignKey( EeAction action, sf::Keyboard::Key key ) {
    // Remove all keys that already map to action
    // TODO: create two separate methods for these operations
    for ( auto i = this->m_key_binding.begin(); i != this->m_key_binding.end(); ) {
        if ( i->second == action ) this->m_key_binding.erase( i++ );
        else ++i;
    }
    // Insert new binding
    this->m_key_binding[key] = action;
}

sf::Keyboard::Key
EController::GetAssignedKey( EeAction action ) const {
    for ( auto pair : this->m_key_binding ) {
        if ( pair.second == action ) return pair.first;
    }
    return sf::Keyboard::Unknown;
}

void
EController::InitializeActions() {
    this->m_action_binding[Accelerate].action = FDerivedAction<nodes::EEntity> (
        EsBoxMover( -1, 0 )
    );

    this->m_action_binding[Decelerate].action = FDerivedAction<nodes::EEntity> (
        EsBoxMover( +1, 0 )
    );
}

bool
EController::IsRealtimeAction( EeAction action ) {
    switch ( action ) {
        case Accelerate:
        case Decelerate:
        // case RotateClockwise:
        // case RotateCounterClockwise:
        // case ActivateWeapon:
            return true;
        default:
            return false;
    }
}


} // namespace ih
