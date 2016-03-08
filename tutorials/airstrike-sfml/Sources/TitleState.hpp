
#pragma once


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "ResourceHolder.hpp"
#include "State.hpp"
#include "StateStack.hpp"
#include "Utility.hpp"


class TitleState : public State {
public:
    TitleState( StateStack& stack, Context context );

    virtual void draw();
    virtual bool update( sf::Time dt );
    virtual bool handleEvent( const sf::Event& event );

private:
    sf::Sprite  mBackgroundSprite;
    sf::Text    mText;

    bool        mShowText;
    sf::Time    mTextEffectTime;
};
