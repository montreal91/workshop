
#ifndef __MENU_STATE_HPP__
#define __MENU_STATE_HPP__

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class MenuState : public State {
public:
    MenuState( StateStack& stack, Context context );

    virtual void    draw();
    virtual bool    update( sf::Time dt );
    virtual bool    handleEvent( const sf::Event& event );

    void            updateOptionText();

private:
    enum OptionNames {
        Play,
        Exit,
    };
    
    sf::Sprite mBackgroundSprite;
    std::vector<sf::Text>  mOptions;
    std::size_t mOptionIndex;

};

#endif