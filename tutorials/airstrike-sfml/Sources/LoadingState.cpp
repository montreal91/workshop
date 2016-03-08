
#include "LoadingState.hpp"


LoadingState::LoadingState( StateStack& stack, Context context ):
State( stack, context ) {
    sf::RenderWindow& window = *getContext().window;
    sf::Font& font = context.fonts->get( Fonts::Main );
    sf::Vector2f viewSize = window.getView().getSize();

    mLoadingText.setFont( font );
    mLoadingText.setString( "Loading Resources" );
    centerOrigin( mLoadingText );
    mLoadingText.setPosition( viewSize.x / 2.0f, viewSize.y / 2.0f + 50.0f );

    mProgressBarBackground.setFillColor( sf::Color::White );
    mProgressBarBackground.setSize( sf::Vector2f( viewSize.x - 20, 10 ) );
    mProgressBarBackground.setPosition( 10, mLoadingText.getPosition().y + 40 );

    mProgressBar.setFillColor( sf::Color( 100, 100, 100 ) );
    mProgressBar.setSize( sf::Vector2f( 200, 10 ) );
    mProgressBar.setPosition( 10, mLoadingText.getPosition().y + 40 );

    setCompletion( 0.0f );

    mLoadingTask.execute();
}

void
LoadingState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.setView( window.getDefaultView() );

    window.draw( mLoadingText );
    window.draw( mProgressBarBackground );
    window.draw( mProgressBar );
}

bool
LoadingState::update( sf::Time dt ) {
    if ( mLoadingTask.isFinished() ) {
        requestStackPop();
        requestStackPush( States::Game );
    } else {
        setCompletion( mLoadingTask.getCompletion() );
    }
    return true;
}

bool
LoadingState::handleEvent( const sf::Event& event ) {
    return true;
}

void
LoadingState::setCompletion( float percent ) {
    if ( percent > 1.0f ) {
        percent = 1.0f;
    }
    // ! Make this shit more readable
    mProgressBar.setSize( 
        sf::Vector2f( 
            mProgressBarBackground.getSize().x * percent, 
            mProgressBar.getSize().y
        ) 
    );
}
