
#include "World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>


World::World( sf::RenderWindow& window ) :
mWindow( window ),
mWorldView( window.getDefaultView() ),
mTextures(),
mSceneGraph(),
mSceneLayers(),
mWorldBounds( 0.0f, 0.0f, mWorldView.getSize().x, 2000.0f ),
mSpawnPosition( mWorldView.getSize().x / 2.0f, mWorldBounds.height - mWorldView.getSize().y / 2.0f ),
mScrollSpeed( -50.0f ),
mPlayerAircraft( nullptr ) {
    loadTextures();
    buildScene();

    mWorldView.setCenter( mSpawnPosition );
}

void
World::update( sf::Time dt ) {
    mWorldView.move( 0.0f, mScrollSpeed * dt.asSeconds() );
    mPlayerAircraft->setVelocity( 0.0f, 0.0f );

    while ( !mCommandQueue.isEmpty() ) {
        mSceneGraph.onCommand( mCommandQueue.pop(), dt );
    }

    adaptPlayerVelocity();

    mSceneGraph.update( dt );
    adaptPlayerPosition();
}

void
World::draw() {
    mWindow.setView( mWorldView );
    mWindow.draw( mSceneGraph );
}

CommandQueue&
World::getCommandQueue() {
    return mCommandQueue;
}

void 
World::loadTextures() {
    mTextures.load( Textures::Eagle, "Media/Textures/Eagle.png" );
    mTextures.load( Textures::Raptor, "Media/Textures/Raptor.png" );
    mTextures.load( Textures::Desert, "Media/Textures/Desert.png" );
}

void
World::buildScene() {
    for ( std::size_t i=0; i<LayerCount; i++ ) {
        SceneNode::Ptr layer( new SceneNode() );
        mSceneLayers[ i ] = layer.get();

        mSceneGraph.attachChild( std::move( layer ) );
    }

    // Prepare the tiled background
    // Wrap up it into a private method later
    sf::Texture& texture = mTextures.get( Textures::Desert );
    sf::IntRect textureRect( mWorldBounds );
    texture.setRepeated( true );

    // Add the background sprite to the scene
    std::unique_ptr<SpriteNode> backgroundSprite( new SpriteNode( texture, textureRect ) );
    backgroundSprite->setPosition( mWorldBounds.left, mWorldBounds.top );
    mSceneLayers[ Background ]->attachChild( std::move( backgroundSprite ) );

    // Add player's aircraft
    std::unique_ptr<Aircraft> leader( new Aircraft( Aircraft::Eagle, mTextures ) );
    mPlayerAircraft = leader.get();
    mPlayerAircraft->setPosition( mSpawnPosition );
    mSceneLayers[ Air ]->attachChild( std::move( leader ) );
}

void
World::adaptPlayerPosition() {
    sf::FloatRect viewBounds(
        mWorldView.getCenter() - mWorldView.getSize() / 2.0f,
        mWorldView.getSize()
    );
    const float borderDistance  = 40.0f;

    sf::Vector2f position       = mPlayerAircraft->getPosition();

    position.x                  = std::max(
        position.x, 
        viewBounds.left + borderDistance
    );

    position.x                  = std::min( 
        position.x, 
        viewBounds.left + viewBounds.width - borderDistance 
    );

    position.y                  = std::max(
        position.y,
        viewBounds.top + borderDistance 
    );

    position.y                  = std::min(
        position.y,
        viewBounds.top + viewBounds.height - borderDistance
    );

    mPlayerAircraft->setPosition( position );
}

void
World::adaptPlayerVelocity() {
    sf::Vector2f velocity = mPlayerAircraft->getVelocity();

    if ( velocity.x != 0.0f && velocity.y != 0.0f ) {
        mPlayerAircraft->setVelocity( velocity / std::sqrt( 2.0f ) );
    }

    mPlayerAircraft->accelerate( 0.0f, mScrollSpeed );
}
