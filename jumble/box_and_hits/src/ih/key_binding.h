
#pragma once


#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <SFML/Window/Keyboard.hpp>


namespace ih {
namespace player_action {
enum EeType {
    MoveForward,
    MoveBackward,
    RotateClockwise,
    RotateCounterClockwise,
    ActivateWeapon,
    DropBomb,
    Count,
};
} // namespace player_action

class EKeyBinding {
public:
    typedef player_action::EeType Action_t;

    explicit EKeyBinding();

    void                    AssignKey( Action_t action, sf::Keyboard::Key key );
    sf::Keyboard::Key       GetAssignedKey( Action_t action ) const;

    bool                    CheckAction( sf::Keyboard::Key key, Action_t& out ) const;
    std::vector<Action_t>   GetActiveRealtimeActions() const;

private:
    // void        InitalizeActions();
    static bool IsRealtimeAction( player_action::EeType action );

    std::map<sf::Keyboard::Key, Action_t> m_key_map;
};

} // namespace ih