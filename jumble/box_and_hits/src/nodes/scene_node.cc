
#include "scene_node.h"


namespace nodes {
ESceneNode::ESceneNode() :
m_children(),
m_parent( nullptr ) {}

void
ESceneNode::AttachChild( Ptr_t child ) {
    child->m_parent = this;
    this->m_children.push_back( std::move( child ) );
}

ESceneNode::Ptr_t
ESceneNode::DetachChild( const ESceneNode& node ) {
    auto found = std::find_if(
        this->m_children.begin(),
        this->m_children.end(),
        [&] ( Ptr_t& p ) {
            return p.get() == &node;
        }
    );
    assert( found != this->m_children.end() );

    Ptr_t result = std::move( *found );
    result->m_parent = nullptr;
    this->m_children.erase( found );
    return result;
}

void
ESceneNode::Update( const sf::Time& dt ) {
    this->UpdateCurrent( dt );
    this->UpdateChildren( dt );
}

void
ESceneNode::UpdateCurrent( const sf::Time& ) {}

void
ESceneNode::UpdateChildren( const sf::Time& dt ) {
    for ( Ptr_t& child : this->m_children ) {
        child->Update( dt );
    }
}

void
ESceneNode::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    // Apply transform of current node
    states.transform *= this->getTransform();

    // Draw node and children with changed transform
    this->DrawCurrent( target, states );
    this->DrawChildren( target, states );
}

void
ESceneNode::DrawCurrent( sf::RenderTarget&, sf::RenderStates ) const {}

void
ESceneNode::DrawChildren( sf::RenderTarget& target, sf::RenderStates states ) const {
    for ( const Ptr_t& child : this->m_children ) {
        child->draw( target, states );
    }
}

sf::Vector2f
ESceneNode::GetWorldPosition() const {
    return this->GetWorldTransform() * sf::Vector2f();
}

sf::Transform
ESceneNode::GetWorldTransform() const {
    sf::Transform transform = sf::Transform::Identity;

    for (const ESceneNode* node = this; node != nullptr; node = node->m_parent ) {
        transform = node->getTransform() * transform;
    }
    return transform;
}

void
ESceneNode::OnCommand( const ih::EsCommand& command, const sf::Time& dt ) {
    if ( command.category & this->GetCategory() ) {
        command.action( *this, dt );
    }

    for ( Ptr_t& child : this->m_children ) {
        child->OnCommand( command, dt );
    }
}

unsigned int
ESceneNode::GetCategory() const {
    return ih::EeCategory::Scene;
}
} // namespace nodes
