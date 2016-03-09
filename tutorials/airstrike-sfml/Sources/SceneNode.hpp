
#pragma once


#include <vector>
#include <set>
#include <memory>
#include <utility>
#include <algorithm>
#include <cassert>
#include <cmath>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Category.hpp"
#include "Command.hpp"
#include "Utility.hpp"


// ??? Why this forward declaration can't be removed?
class CommandQueue;


class SceneNode :
    public sf::Transformable,
    public sf::Drawable,
    private sf::NonCopyable {
public:
    typedef std::unique_ptr<SceneNode>          Ptr;
    typedef std::pair<SceneNode*, SceneNode*>   Pair;

    explicit                SceneNode(
        Category::Type category = Category::None
    );

    void                    AttachChild( Ptr child );
    Ptr                     DetachChild( const SceneNode& node );

    void                    Update( sf::Time dt, CommandQueue& commands );

    sf::Vector2f            GetWorldPosition() const;
    sf::Transform           GetWorldTransform() const;

    void                    OnCommand( const Command& command, sf::Time td );
    virtual unsigned int    GetCategory() const;

    void                    CheckSceneCollision(
        SceneNode& sceneGraph,
        std::set<Pair>& collisionPairs
    );
    void                    CheckNodeCollision(
        SceneNode& node,
        std::set<Pair>& collisionPairs
    );
    void                    RemoveWrecks();
    virtual sf::FloatRect   GetBoundingRect() const;
    virtual bool            IsMarkedForRemoval() const;
    virtual bool            IsDestroyed() const;

private:
    virtual void        UpdateCurrent( sf::Time dt, CommandQueue& commands );
    void                UpdateChildren( sf::Time dt, CommandQueue& commands );

    virtual void        draw(
        sf::RenderTarget& target,
        sf::RenderStates states
    ) const;
    virtual void        DrawCurrent(
        sf::RenderTarget& target,
        sf::RenderStates states
    ) const;
    void                DrawChildren(
        sf::RenderTarget& target,
        sf::RenderStates states
    ) const;
    void                DrawBoundingRect(
        sf::RenderTarget& target,
        sf::RenderStates states
    ) const;

    std::vector<Ptr>    mChildren;
    SceneNode*          mParent;
    Category::Type      mDefaultCategory;
};

bool    Collision( const SceneNode& lhs, const SceneNode& rhs );
float   Distance( const SceneNode& lhs, const SceneNode& rhs );
