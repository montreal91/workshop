
#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__


#include "Command.hpp"

#include <SFML/Window/Event.hpp>

#include <map>

class CommandQueue;

class Player {
public:
    enum Action {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
        ActionCount,
    };

    Player();

    void                handleEvent( const sf::Event& event, CommandQueue& commands );
    void                handleRealtimeInput( CommandQueue& commands );

    void                assignKey( Action action, sf::Keyboard::Key key );
    sf::Keyboard::Key   getAssignedKey( Action action ) const;

private:
    void                                initalizeActions();
    static bool                         isRealtimeAction( Action action );

    std::map<sf::Keyboard::Key, Action> mKeyBinding;
    std::map<Action, Command>           mActionBinding;
};

#endif
