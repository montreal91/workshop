
#pragma once

#include <cassert>
#include <functional>

#include <SFML/System/Time.hpp>

#include "category.h"
#include "src/nodes/scene_node.h"

namespace nodes {
class ESceneNode;
} // namespace nodes

namespace ih {
struct EsCommand {
    typedef std::function<void( nodes::ESceneNode&, const sf::Time& )> Action_t;

    EsCommand();
    Action_t        action;
    unsigned int    category;
};

template <typename GameObject, typename Function>
EsCommand::Action_t
FDerivedAction( Function fun ) {
    return [=]( nodes::ESceneNode& node, const sf::Time& dt) {
        // Check if cast safe
        assert( dynamic_cast<GameObject*>( &node ) != nullptr );

        // Downcast node and invoke function on it
        fun( static_cast<GameObject&>( node ), dt );
    };
}

} // namespace ih
