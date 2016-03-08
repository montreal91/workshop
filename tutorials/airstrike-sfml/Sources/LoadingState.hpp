
#pragma once


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>

#include "ParallelTask.hpp"
#include "ResourceHolder.hpp"
#include "State.hpp"
#include "Utility.hpp"


class LoadingState : public State {
public:
    LoadingState( StateStack& stack, Context context );

    virtual void    draw();
    virtual bool    update( sf::Time dt );
    virtual bool    handleEvent( const sf::Event& event );

    void            setCompletion( float percent );

private:
    sf::Text            mLoadingText;
    sf::RectangleShape  mProgressBarBackground;
    sf::RectangleShape  mProgressBar;

    ParallelTask        mLoadingTask;
};
