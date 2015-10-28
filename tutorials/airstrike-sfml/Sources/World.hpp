
#ifndef __WORLD_HPP__
#define __WORLD_HPP__


#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Aircraft.hpp"
#include "CommandQueue.hpp"
#include "Command.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <queue>


namespace sf {
    class RenderWindow;
}


class World : private sf::NonCopyable {
public:
    explicit        World( sf::RenderWindow& window );

    void            update( sf::Time dt );
    void            draw();

    CommandQueue&   getCommandQueue();

private:
    void loadTextures();
    void buildScene();
    void adaptPlayerPosition();
    void adaptPlayerVelocity();

    enum Layer {
        Background,
        Air,
        LayerCount,
    };

    sf::RenderWindow&                   mWindow;
    sf::View                            mWorldView;
    TextureHolder                       mTextures;

    SceneNode                           mSceneGraph;
    std::array<SceneNode*, LayerCount>  mSceneLayers;
    CommandQueue                        mCommandQueue;

    sf::FloatRect                       mWorldBounds;
    sf::Vector2f                        mSpawnPosition;
    float                               mScrollSpeed;
    Aircraft*                           mPlayerAircraft;

};

#endif
