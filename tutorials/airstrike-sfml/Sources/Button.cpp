
#include "Button.hpp"
#include "Utility.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI {

Button::Button( const FontHolder& fonts, const TextureHolder& textures ) :
mCallback(),
mNormalTexture( textures.get( Textures::ButtonNormal ) ),
mSelectedTexture( textures.get( Textures::ButtonSelected ) ),
mPressedTexture( textures.get( Textures::ButtonPressed ) ),
mSprite(),
mText( "", fonts.get( Fonts::Main ), 16 ),
mIsToggle( false ) {
    mSprite.setTexture( mNormalTexture );

    sf::FloatRect bounds = mSprite.getLocalBounds();
    mText.setPosition( bounds.width / 2.0f, bounds.height / 2.0f );
}

void
Button::setCallback( Callback callback ) {
    mCallback = std::move( callback );
}

void
Button::setText( const std::string& text ) {
    mText.setString( text );
    centerOrigin( mText );
}

void
Button::setToggle( bool flag ) {
    mIsToggle = flag;
}

bool
Button::isSelectable() const {
    return true;
}

void
Button::select() {
    Component::select();

    mSprite.setTexture( mSelectedTexture );
}

void
Button::deselect() {
    Component::deselect();

    mSprite.setTexture( mNormalTexture );
}

void
Button::activate() {
    Component::activate();

    if ( mIsToggle ) {
        mSprite.setTexture( mPressedTexture );
    }
    if ( mCallback ) {
        mCallback();
    }
    if ( !mIsToggle ) {
        deactivate();
    }
}

void
Button::deactivate() {
    Component::deactivate();

    if( mIsToggle ) {
        if ( isSelected() ) {
            mSprite.setTexture( mSelectedTexture );
        } else {
            mSprite.setTexture( mNormalTexture );
        }
    }
}

void
Button::handleEvent( const sf::Event& event ) {}

void
Button::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    states.transform *= getTransform();
    target.draw( mSprite, states );
    target.draw( mText, states );
}

} // namespace GUI
