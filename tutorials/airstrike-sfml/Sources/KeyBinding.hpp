
#ifndef __KEY_BINDING_HPP__
#define __KEY_BINDING_HPP__

#include <SFML/Window/Keyboard.hpp>

#include <map>
#include <vector>

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

#endif // __KEY_BINDING_HPP__
