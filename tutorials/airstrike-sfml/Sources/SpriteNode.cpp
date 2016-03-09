
#include "SpriteNode.hpp"


SpriteNode::SpriteNode( const sf::Texture& texture ) :
mSprite( texture ) {}

SpriteNode::SpriteNode(
    const sf::Texture& texture,
    const sf::IntRect& textureRect
) :
mSprite( texture, textureRect ) {}

void
SpriteNode::DrawCurrent(
    sf::RenderTarget& target,
    sf::RenderStates states
) const {
    target.draw( mSprite, states );
}
