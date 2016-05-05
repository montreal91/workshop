
#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "scene_node.h"


namespace nodes {
class ESpriteNode : public ESceneNode {
public:
    explicit ESpriteNode( const sf::Texture& texture );
    ESpriteNode( const sf::Texture& texture, const sf::IntRect& texture_rect );

private:
    virtual void DrawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;

    sf::Sprite m_sprite;
};

} // namespace nodes
