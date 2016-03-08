
#include "Application.hpp"


const sf::Time Application::TimePerFrame = sf::seconds( 1.0f / 60.0f );


Application::Application() :
mWindow( sf::VideoMode( 1024, 768 ), "Network", sf::Style::Close ),
mTextures(),
mFonts(),
mMusic(),
mSounds(),
mKeyBinding1( 1 ),
mKeyBinding2( 2 ),
mStateStack( State::Context( mWindow, mTextures, mFonts, mMusic, mSounds, mKeyBinding1, mKeyBinding2 ) ),
mStatisticsText(),
mStatisticsUpdateTime(),
mStatisticsNumFrames( 0 ) {
    mWindow.setKeyRepeatEnabled( false );
    mWindow.setVerticalSyncEnabled( true );

    mFonts.load( Fonts::Main, "Media/Sansation.ttf" );

    mTextures.load( Textures::TitleScreen, "Media/Textures/TitleScreen.png" );
    mTextures.load( Textures::Buttons, "Media/Textures/Buttons.png" );

    mStatisticsText.setFont( mFonts.get( Fonts::Main ) );
    mStatisticsText.setPosition( 5.0f, 5.0f );
    mStatisticsText.setCharacterSize( 10u );

    registerStates();
    mStateStack.pushState( States::Title );

    mMusic.setVolume( 25.0f );
}

void
Application::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while ( mWindow.isOpen() ) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while ( timeSinceLastUpdate > TimePerFrame ) {
            timeSinceLastUpdate -= TimePerFrame;
            
            processInput();
            update( TimePerFrame );

            if ( mStateStack.isEmpty() ) {
                mWindow.close();
            }
        }
        updateStatistics( dt );
        render();
    }
}

void
Application::processInput() {
    sf::Event event;
    while ( mWindow.pollEvent( event ) ) {
        mStateStack.handleEvent( event );

        if ( event.type == sf::Event::Closed ) {
            mWindow.close();
        }
    }
}

void
Application::update( sf::Time dt ) {
    mStateStack.update( dt );
}

void
Application::render() {
    mWindow.clear();

    mStateStack.draw();

    mWindow.setView( mWindow.getDefaultView() );
    mWindow.draw( mStatisticsText );

    mWindow.display();
}

void
Application::updateStatistics( sf::Time dt ) {
    mStatisticsUpdateTime += dt;
    mStatisticsNumFrames += 1;

    if ( mStatisticsUpdateTime >= sf::seconds( 1.0f ) ) {
        mStatisticsText.setString( "FPS: " + std::to_string( mStatisticsNumFrames ) );

        mStatisticsUpdateTime -= sf::seconds( 1.0f );
        mStatisticsNumFrames = 0;
    }
}

void
Application::registerStates() {
    mStateStack.registerState<TitleState>( States::Title );
    mStateStack.registerState<MenuState>( States::Menu );
    mStateStack.registerState<GameState>( States::Game ); // TODO: rename States::Game -> States::SingleplayerGame
    mStateStack.registerState<MultiplayerGameState>( States::HostGame, true );
    mStateStack.registerState<MultiplayerGameState>( States::JoinGame, false );
    mStateStack.registerState<PauseState>( States::Pause ); // TODO: rename States::Pause -> States::SingleplayerPause
    mStateStack.registerState<PauseState>( States::NetworkPause, true );
    mStateStack.registerState<SettingsState>( States::Settings );
    mStateStack.registerState<GameOverState>( States::GameOver, "Mission Failed!" );
    mStateStack.registerState<GameOverState>( States::MissionSuccess, "Mission Successful!" );
}
