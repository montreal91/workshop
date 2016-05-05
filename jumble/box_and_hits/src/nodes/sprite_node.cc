
#include "sprite_node.h"

namespace nodes {
ESpriteNode::ESpriteNode( const sf::Texture& texture ) :
m_sprite( texture ) {}

ESpriteNode::ESpriteNode( const sf::Texture& texture, const sf::IntRect& texture_rect ) :
m_sprite( texture, texture_rect ) {}

void
ESpriteNode::DrawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.draw( this->m_sprite, states );
}

} // namespace nodes
