
#include "Label.hpp"


namespace GUI {

Label::Label( const std::string& text, const FontHolder& fonts ) :
mText( text, fonts.get( Fonts::Main ), 16 ) {}

bool
Label::isSelectable() const {
    return false;
}

void
Label::handleEvent( const sf::Event& event ) {}

void
Label::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    states.transform *= getTransform();
    target.draw( mText, states );
}

void
Label::setText( const std::string& text ) {
    mText.setString( text );
}
} // namespace GUI
