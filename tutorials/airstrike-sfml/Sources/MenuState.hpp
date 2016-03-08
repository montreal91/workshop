
#pragma once


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>

#include "Button.hpp"
#include "Container.hpp"
#include "MusicPlayer.hpp"
#include "ResourceHolder.hpp"
#include "State.hpp"
#include "Utility.hpp"


class MenuState : public State {
public:
    MenuState( StateStack& stack, Context context );

    virtual void    draw();
    virtual bool    update( sf::Time dt );
    virtual bool    handleEvent( const sf::Event& event );

private:
    sf::Sprite      mBackgroundSprite;
    GUI::Container  mGUIContainer;
};
