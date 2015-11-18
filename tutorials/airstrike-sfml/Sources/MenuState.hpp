
#ifndef __MENU_STATE_HPP__
#define __MENU_STATE_HPP__

#include "State.hpp"
#include "Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


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

#endif // __MENU_STATE_HPP__
