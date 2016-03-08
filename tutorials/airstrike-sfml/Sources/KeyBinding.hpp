
#pragma once


#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <SFML/Window/Keyboard.hpp>


namespace PlayerAction {
enum Type {
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    Fire,
    LaunchMissile,
    Count,
};

} // PlayerAction

class KeyBinding {
public:
    typedef PlayerAction::Type Action;

    explicit KeyBinding( int controlPreconfiguration );

    void                assignKey( Action action, sf::Keyboard::Key key );
    sf::Keyboard::Key   getAssignedKey( Action action ) const;

    bool                checkAction( sf::Keyboard::Key key, Action& out ) const;
    std::vector<Action> getRealtimeActions() const;

private:
    void initalizeActions();

    std::map<sf::Keyboard::Key, Action> mKeyMap;
};

// TODO: put it into class
bool isRealtimeAction( PlayerAction::Type action );
