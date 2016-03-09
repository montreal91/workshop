
#include "NetworkNode.hpp"


NetworkNode::NetworkNode() :
SceneNode(),
mPendingActions() {}


unsigned int
NetworkNode::GetCategory() const {
    return Category::Network;
}

void
NetworkNode::NotifyGameAction(
    GameActions::Type type,
    sf::Vector2f position
) {
    mPendingActions.push( GameActions::Action( type, position ) );
}

bool
NetworkNode::PollGameAction( GameActions::Action& out ) {
    if ( mPendingActions.empty() ) {
        return false;
    } else {
        out = mPendingActions.front();
        mPendingActions.pop();
        return true;
    }
}
