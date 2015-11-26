
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
    explicit        World( sf::RenderWindow& window, FontHolder& fonts );

    void            update( sf::Time dt );
    void            draw();

    CommandQueue&   getCommandQueue();

    bool            hasAlivePlayer() const;
    bool            hasPlayerReachedEnd() const;

private:
    void            loadTextures();
    void            adaptPlayerPosition();
    void            adaptPlayerVelocity();
    void            handleCollisions();

    void            buildScene();
    void            addEnemies();
    void            addEnemy( Aircraft::Type type, float relX, float relY );
    void            spawnEnemies();
    void            destroyEntitiesOutsideView();
    void            guideMissiles();

    sf::FloatRect   getViewBounds() const;
    sf::FloatRect   getBattlefieldBounds() const;

    enum Layer {
        Background,
        Air,
        LayerCount,
    };

    struct SpawnPoint {
        SpawnPoint( Aircraft::Type type, float x, float y ) :
        type( type ),
        x( x ),
        y( y ) {}

        Aircraft::Type  type;
        float           x;
        float           y;
    };

    sf::RenderWindow&                   mWindow;
    sf::View                            mWorldView;
    FontHolder&                         mFonts;
    TextureHolder                       mTextures;

    SceneNode                           mSceneGraph;
    std::array<SceneNode*, LayerCount>  mSceneLayers;
    CommandQueue                        mCommandQueue;

    sf::FloatRect                       mWorldBounds;
    sf::Vector2f                        mSpawnPosition;
    float                               mScrollSpeed;
    Aircraft*                           mPlayerAircraft;

    std::vector<SpawnPoint>             mEnemySpawnPoints;
    std::vector<Aircraft*>              mActiveEnemies;

};

#endif // __WORLD_HPP__
