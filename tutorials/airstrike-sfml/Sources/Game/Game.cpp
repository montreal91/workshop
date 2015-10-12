
#include "Game.h"

const float Game::PlayerSpeed       = 100.0f;
const sf::Time Game::TimePerFrame   = sf::seconds( 1.0f / 60.0f );

Game::Game() :
    mWindow( sf::VideoMode( 640, 480 ), "SFML Application", sf::Style::Close ),
    mTexture(),
    mPlayer(),
    mFont(),
    mStatisticsText(),
    mStatisticsUpdateTime(),
    mStatisticsNumFrames( 0 ),
    mIsMovingUp( false ),
    mIsMovingDown( false ),
    mIsMovingRight( false ),
    mIsMovingLeft( false ) {
        if( !mTexture.loadFromFile( "Media/Textures/Eagle.png" ) ) {
            // Handle loading error
            std::cout << "Fart!\n";
        }

        mPlayer.setTexture( mTexture );
        mPlayer.setPosition( 100.0f, 100.0f );

        mFont.loadFromFile( "Media/Sansation.ttf" );
        mStatisticsText.setFont( mFont );
        mStatisticsText.setPosition( 5.0f, 5.0f );
        mStatisticsText.setCharacterSize( 10 );
}


void
Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while ( mWindow.isOpen() ) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while ( timeSinceLastUpdate > TimePerFrame ) {
            timeSinceLastUpdate -= TimePerFrame;

            processEvents();
            update( TimePerFrame );
        }
        updateStatistics( elapsedTime );
        render();
    }
}


void
Game::processEvents() {
    sf::Event event;
    while ( mWindow.pollEvent( event ) ) {
        if ( event.type == sf::Event::KeyPressed ) {
            handlePlayerInput( event.key.code, true );
        } else if ( event.type == sf::Event::KeyReleased ) {
            handlePlayerInput( event.key.code, false );
        } else if ( event.type == sf::Event::Closed ) {
            mWindow.close();
        } else {
            break;
        }
    }
}


void
Game::update( sf::Time elapsedTime ) {
    sf::Vector2f movement( 0.0f, 0.0f );
    if ( mIsMovingUp ) {
        movement.y -= PlayerSpeed;
    }
    if ( mIsMovingDown ) {
        movement.y += PlayerSpeed;
    }
    if ( mIsMovingLeft ) {
        movement.x -= PlayerSpeed;
    }
    if ( mIsMovingRight ) {
        movement.x += PlayerSpeed;
    }

    mPlayer.move( movement * elapsedTime.asSeconds() );
}


void
Game::render() {
    mWindow.clear();
    mWindow.draw( mPlayer );
    mWindow.draw( mStatisticsText );
    mWindow.display();
}


void
Game::updateStatistics( sf::Time elapsedTime ) {
    mStatisticsUpdateTime += elapsedTime;
    mStatisticsNumFrames += 1;

    if ( mStatisticsUpdateTime >= sf::seconds( 1.0f ) ) {
        mStatisticsText.setString(
            "Frames / Second = " + std::to_string( mStatisticsNumFrames ) + "\n" +
            "Time / Update   = " + std::to_string( mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames ) +
            "us"
        );
        mStatisticsUpdateTime -= sf::seconds( 1.0f );
        mStatisticsNumFrames = 0;
    }
}


void
Game::handlePlayerInput( sf::Keyboard::Key key, bool isPressed ) {
    if ( key == sf::Keyboard::W ) {
        mIsMovingUp = isPressed;
    } else if ( key == sf::Keyboard::S ) {
        mIsMovingDown = isPressed;
    } else if ( key == sf::Keyboard::A ) {
        mIsMovingLeft = isPressed;
    } else if ( key == sf::Keyboard::D ) {
        mIsMovingRight = isPressed;
    }
}