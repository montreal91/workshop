
#ifndef __TEXT_NODE_HPP__
#define __TEXT_NODE_HPP__


#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>


class TextNode : public SceneNode {
public:
    explicit    TextNode( const FontHolder& fonts, const std::string& text );

    void        setString( const std::string& text );

private:
    virtual void    drawCurrent(
        sf::RenderTarget& target,
        sf::RenderStates states
    ) const;

    sf::Text        mText;
};

#endif //__TEXT_NODE_HPP__
