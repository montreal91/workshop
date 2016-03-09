
#pragma once


#include <queue>

#include <SFML/System/Vector2.hpp>

#include "NetworkProtocol.hpp"
#include "SceneNode.hpp"


class NetworkNode : public SceneNode {
public:
    NetworkNode();

    void                    NotifyGameAction(
        GameActions::Type type,
        sf::Vector2f position
    );
    bool                    PollGameAction( GameActions::Action& out );

    virtual unsigned int    GetCategory() const;

private:
    std::queue<GameActions::Action> mPendingActions;
};
