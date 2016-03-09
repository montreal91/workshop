
#include "TextNode.hpp"


TextNode::TextNode( const FontHolder& fonts, const std::string& text ) {
    mText.setFont( fonts.get( Fonts::Main ) );
    mText.setCharacterSize( 20 );
    SetString( text );
}

void
TextNode::DrawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.draw( mText, states );
}

void
TextNode::SetString( const std::string& text ) {
    mText.setString( text );
    centerOrigin( mText );
}
