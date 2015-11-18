
#ifndef __GAME_OVER_STATE_HPP__
#define __GAME_OVER_STATE_HPP__


#include "State.hpp"
#include "Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameOverState : public State {
public:
    GameOverState( StateStack& stack, Context context );

    virtual void draw();
    virtual bool update( sf::Time dt );
    virtual bool handleEvent( const sf::Event& event );

private:
    sf::Text mGameOverText;
    sf::Time mElapsedTime;

};

#endif
