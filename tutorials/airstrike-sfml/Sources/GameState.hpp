
#pragma once


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "MusicPlayer.hpp"
#include "Player.hpp"
#include "State.hpp"
#include "StateStack.hpp"
#include "World.hpp"


class GameState : public State {
public:
    GameState( StateStack& stack, Context context );
    
    virtual void draw();
    virtual bool update( sf::Time dt );
    virtual bool handleEvent( const sf::Event& event );

private:
    World   mWorld;
    Player  mPlayer;
};
