
#pragma once


#include <queue>

#include <SFML/System/Vector2.hpp>

#include "SceneNode.hpp"
#include "NetworkProtocol.hpp"


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
