
#include "SceneNode.hpp"
#include "CommandQueue.hpp"


SceneNode::SceneNode( Category::Type category ) :
mChildren(),
mParent( nullptr ),
mDefaultCategory( category ) {}

void
SceneNode::AttachChild( Ptr child ) {
    child->mParent = this;
    mChildren.push_back( std::move( child ) );
}

SceneNode::Ptr
SceneNode::DetachChild( const SceneNode& node ) {
    auto found = std::find_if(
        mChildren.begin(),
        mChildren.end(),
        [&] ( Ptr& p ) { return p.get() == &node; }
    );
    assert( found != mChildren.end() );

    Ptr result      = std::move( *found );
    result->mParent = nullptr;
    mChildren.erase( found );
    return result;
}

void
SceneNode::Update( sf::Time dt, CommandQueue& commands ) {
    UpdateCurrent( dt, commands );
    UpdateChildren( dt, commands );
}

void
SceneNode::UpdateCurrent( sf::Time dt, CommandQueue& commands ) {}

void
SceneNode::UpdateChildren( sf::Time dt, CommandQueue& commands ) {
    for ( Ptr& child : mChildren ) {
        child->Update( dt, commands );
    }
}

void
SceneNode::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    states.transform *= getTransform();

    DrawCurrent( target, states );
    DrawChildren( target, states );
}

void
SceneNode::DrawCurrent(
    sf::RenderTarget& target,
    sf::RenderStates states
) const {}

void
SceneNode::DrawChildren(
    sf::RenderTarget& target,
    sf::RenderStates states
) const {
    for ( const Ptr& child : mChildren ) {
        child->draw( target, states );
    }
}

void
SceneNode::DrawBoundingRect(
    sf::RenderTarget& target,
    sf::RenderStates
) const {
    sf::FloatRect rect = GetBoundingRect();

    sf::RectangleShape shape;
    shape.setPosition( sf::Vector2f( rect.left, rect.top ) );
    shape.setSize( sf::Vector2f( rect.width, rect.height ) );
    shape.setFillColor( sf::Color::Transparent );
    shape.setOutlineColor( sf::Color::Green );
    shape.setOutlineThickness( 1.0f );

    target.draw( shape );
}

sf::Vector2f
SceneNode::GetWorldPosition() const {
    return GetWorldTransform() * sf::Vector2f();
}

sf::Transform
SceneNode::GetWorldTransform() const {
    sf::Transform transform = sf::Transform::Identity;

    for ( const SceneNode* node = this; node != nullptr; node=node->mParent ) {
        transform = node->getTransform() * transform;
    }
    return transform;
}

void
SceneNode::OnCommand( const Command& command, sf::Time dt ) {
    if ( command.category & GetCategory() ) {
        command.action( *this, dt );
    }

    for( Ptr& child : mChildren ) {
        child->OnCommand( command, dt );
    }
}

unsigned int
SceneNode::GetCategory() const {
    return mDefaultCategory;
}

void
SceneNode::CheckSceneCollision(
    SceneNode& sceneGraph,
    std::set<Pair>& collisionPairs
) {
    CheckNodeCollision( sceneGraph, collisionPairs );

    for( Ptr& child : sceneGraph.mChildren ) {
        CheckSceneCollision( *child, collisionPairs );
    }
}

// WARNING: recursive
void
SceneNode::CheckNodeCollision(
    SceneNode& node,
    std::set<Pair>& collisionPairs
) {
    // TODO: put this complex condition into function
    if ( this != &node && Collision( *this, node ) && !IsDestroyed() && !node.IsDestroyed() ) {
        collisionPairs.insert( std::minmax( this, &node ) );
    }
    for( Ptr& child : mChildren ) {
        child->CheckNodeCollision( node, collisionPairs );
    }
}

void
SceneNode::RemoveWrecks() {
    auto wreckFieldBegin = std::remove_if(
        mChildren.begin(),
        mChildren.end(),
        std::mem_fn( &SceneNode::IsMarkedForRemoval )
    );
    mChildren.erase( wreckFieldBegin, mChildren.end() );

    std::for_each(
        mChildren.begin(),
        mChildren.end(),
        std::mem_fn( &SceneNode::RemoveWrecks )
    );
}

sf::FloatRect
SceneNode::GetBoundingRect() const {
    return sf::FloatRect();
}

bool
SceneNode::IsMarkedForRemoval() const {
    return IsDestroyed();
}

bool
SceneNode::IsDestroyed() const {
    return false;
}

bool
Collision( const SceneNode& lhs, const SceneNode& rhs ) {
    return lhs.GetBoundingRect().intersects( rhs.GetBoundingRect() );
}

float
Distance( const SceneNode& lhs, const SceneNode& rhs ) {
    return length( lhs.GetWorldPosition() - rhs.GetWorldPosition() );
}
