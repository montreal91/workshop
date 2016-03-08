
#pragma once


#include <string>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "Utility.hpp"


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
