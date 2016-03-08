
#pragma once


#include <cassert>
#include <functional>

#include <SFML/System/Time.hpp>

#include "Category.hpp"


class SceneNode;

struct Command {
    typedef std::function<void( SceneNode&, sf::Time )> Action;

    Command();

    Action          action;
    unsigned int    category;
};

template <typename GameObject, typename Function>
Command::Action derivedAction( Function fn ) {
    return [=] ( SceneNode& node, sf::Time dt ) {
        // Check if cast is safe
        assert( dynamic_cast<GameObject*>( &node ) != nullptr );

        // Downcast node and invoke function on it
        fn( static_cast<GameObject&>( node ), dt );

    };
}
