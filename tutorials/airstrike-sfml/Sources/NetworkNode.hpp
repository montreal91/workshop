
#ifndef __NETWORK_NODE_HPP__
#define __NETWORK_NODE_HPP__


#include "SceneNode.hpp"
#include "NetworkProtocol.hpp"

#include <queue>


class NetworkNode : public SceneNode {
public:
    NetworkNode();

    void                    notifyGameAction(
        GameActions::Type type,
        sf::Vector2f position
    );
    bool                    pollGameAction( GameActions::Action& out );

    virtual unsigned int    getCategory() const;

private:
    std::queue<GameActions::Action> mPendingActions;
};

#endif // __NETWORK_NODE_HPP__
