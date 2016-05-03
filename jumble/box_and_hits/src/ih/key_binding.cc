
#include "key_binding.h"

namespace ih {
EKeyBinding::EKeyBinding() {
    // TODO: make this staff load from configs
    this->m_key_map[sf::Keyboard::Up]       = player_action::MoveForward;
    this->m_key_map[sf::Keyboard::Down]     = player_action::MoveBackward;
    this->m_key_map[sf::Keyboard::Left]     = player_action::RotateClockwise;
    this->m_key_map[sf::Keyboard::Right]    = player_action::RotateCounterClockwise;
    this->m_key_map[sf::Keyboard::Space]    = player_action::ActivateWeapon;
    this->m_key_map[sf::Keyboard::LAlt]     = player_action::DropBomb;
}

void
EKeyBinding::AssignKey( Action_t action, sf::Keyboard::Key key ) {
    // Remove all keys that already map to action
    // TODO: create two separate methods for these operations
    for ( auto i = this->m_key_map.begin(); i != this->m_key_map.end(); ) {
        if ( i->second == action ) this->m_key_map.erase( i++ );
        else ++i;
    }
    // Insert new binding
    this->m_key_map[key] = action;
}

sf::Keyboard::Key
EKeyBinding::GetAssignedKey( Action_t action ) const {
    for ( auto pair : this->m_key_map ) {
        if ( pair.second == action ) return pair.first;
    }
    return sf::Keyboard::Unknown;
}

std::vector<EKeyBinding::Action_t>
EKeyBinding::GetActiveRealtimeActions() const {
    std::vector<Action_t> actions;

    for ( auto pair : this->m_key_map ) {
        // TODO: put this condition into method
        if ( sf::Keyboard::isKeyPressed( pair.first ) && this->IsRealtimeAction( pair.second ) ) {
            actions.push_back( pair.second );
        }
    }
    return actions;
}

bool
EKeyBinding::IsRealtimeAction( player_action::EeType action ) {
    switch ( action ) {
        case player_action::MoveForward:
        case player_action::MoveBackward:
        case player_action::RotateClockwise:
        case player_action::RotateCounterClockwise:
        case player_action::ActivateWeapon:
            return true;
        default:
            return false;
    }
}

} // namespace ih
