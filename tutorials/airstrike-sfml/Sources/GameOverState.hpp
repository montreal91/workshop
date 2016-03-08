
#pragma once


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>


#include "Container.hpp"
#include "Player.hpp"
#include "ResourceHolder.hpp"
#include "State.hpp"
#include "StateStack.hpp"
#include "Utility.hpp"


class GameOverState : public State {
public:
    GameOverState( StateStack& stack, Context context, const std::string& text );

    virtual void draw();
    virtual bool update( sf::Time dt );
    virtual bool handleEvent( const sf::Event& event );

private:
    sf::Text mGameOverText;
    sf::Time mElapsedTime;
};
