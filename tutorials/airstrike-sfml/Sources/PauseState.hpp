
#pragma once


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>

#include "Button.hpp"
#include "Container.hpp"
#include "MusicPlayer.hpp"
#include "ResourceHolder.hpp"
#include "State.hpp"
#include "StateStack.hpp"
#include "Utility.hpp"


class PauseState : public State {
public:
    PauseState(
        StateStack& stack,
        Context context,
        bool letUpdatesThrough=false
    );
    ~PauseState();

    virtual void draw();
    virtual bool update( sf::Time dt );
    virtual bool handleEvent( const sf::Event& event );

private:
    sf::Sprite      mBackgroundSprite;
    sf::Text        mPausedText;
    GUI::Container  mGUIContainer;
    bool            mLetUpdatesThrough;
};
