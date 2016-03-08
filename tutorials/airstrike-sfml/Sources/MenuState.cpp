
#include "MenuState.hpp"


MenuState::MenuState( StateStack& stack, Context context ) :
State( stack, context ),
mGUIContainer() {
    sf::Texture& texture = context.textures->get( Textures::TitleScreen );
    mBackgroundSprite.setTexture( texture );

    auto playButton = std::make_shared<GUI::Button>( context );
    playButton->setPosition( 100, 300 );
    playButton->setText( "Play" );
    playButton->setCallback( [this] () {
        requestStackPop();
        requestStackPush( States::Game );
    });

    auto hostButton = std::make_shared<GUI::Button>( context );
    hostButton->setPosition( 100, 350 );
    hostButton->setText( "Host" );
    hostButton->setCallback( [this] () {
        requestStackPop();
        requestStackPush( States::HostGame );
    });

    auto joinButton = std::make_shared<GUI::Button>( context );
    joinButton->setPosition( 100, 400 );
    joinButton->setText( "Join" );
    joinButton->setCallback( [this] () {
        requestStackPop();
        requestStackPush( States::JoinGame );
    });

    auto settingsButton = std::make_shared<GUI::Button>( context );
    settingsButton->setPosition( 100, 450 );
    settingsButton->setText( "Settings" );
    settingsButton->setCallback( [this] () {
        requestStackPush( States::Settings );
    });

    auto exitButton = std::make_shared<GUI::Button>( context );
    exitButton->setPosition( 100, 500 );
    exitButton->setText( "Exit" );
    exitButton->setCallback( [this] () {
        requestStackPop();
    });

    mGUIContainer.pack( playButton );
    mGUIContainer.pack( hostButton );
    mGUIContainer.pack( joinButton );
    mGUIContainer.pack( settingsButton );
    mGUIContainer.pack( exitButton );

    context.music->play( Music::MenuTheme );
}

void 
MenuState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.setView( window.getDefaultView() );

    window.draw( mBackgroundSprite );
    window.draw( mGUIContainer );
}

bool
MenuState::update( sf::Time dt ) {
    return true;
}

bool
MenuState::handleEvent( const sf::Event& event ) {
    mGUIContainer.handleEvent( event );
    return false;
}
