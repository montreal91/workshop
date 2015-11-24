
#include "SettingsState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


SettingsState::SettingsState( StateStack& stack, Context context ) :
State( stack, context ),
mGUIContainer() {
    mBackgroundSprite.setTexture( context.textures->get( Textures::TitleScreen ) );

    // Build key binding buttons and labels
    // TODO: put it into a private method
    addButtonLabel( Player::MoveLeft, 300.0f, "Move Left", context );
    addButtonLabel( Player::MoveRight, 350.0f, "Move Right", context );
    addButtonLabel( Player::MoveUp, 400.0f, "Move Up", context );
    addButtonLabel( Player::MoveDown, 450.0f, "Move Down", context );
    addButtonLabel( Player::Fire, 500.0f, "Fire", context );
    addButtonLabel( Player::LaunchMissile, 550.0f, "Missile", context );

    updateLabels();

    auto backButton = std::make_shared<GUI::Button>( *context.fonts, *context.textures );
    backButton->setPosition( 80.0f, 620.0f );
    backButton->setText( "Back" );
    backButton->setCallback( std::bind( &SettingsState::requestStackPop, this ) );

    mGUIContainer.pack( backButton );
}

void
SettingsState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw( mBackgroundSprite );
    window.draw( mGUIContainer );
}

bool
SettingsState::update( sf::Time ) {
    return true;
}

bool SettingsState::handleEvent( const sf::Event& event ) {
    bool isKeyBinding = false;

    // TODO: try to refactor it for better readability
    for ( std::size_t action=0; action<Player::ActionCount; action++ ) {
        if ( mBindingButtons[action]->isActive() ) {
            isKeyBinding = true;
            if ( event.type == sf::Event::KeyReleased ) {
                getContext().player->assignKey(
                    static_cast<Player::Action>( action ),
                    event.key.code
                );
                mBindingButtons[action]->deactivate();
            }
            break;
        }
    }
    if ( isKeyBinding ) {
        updateLabels();
    } else {
        mGUIContainer.handleEvent( event );
    }
    return false;
}

void
SettingsState::updateLabels() {
    Player& player = *getContext().player;

    for ( std::size_t i=0; i<Player::ActionCount; i++ ) {
        sf::Keyboard::Key key = player.getAssignedKey( static_cast<Player::Action>( i ) );
        mBindingLabels[i]->setText( std::to_string( key ) );
    }
}

void
SettingsState::addButtonLabel(
    Player::Action action,
    float y,
    const std::string& text,
    Context context
) {
    mBindingButtons[action] = std::make_shared<GUI::Button>( *context.fonts, *context.textures );
    mBindingButtons[action]->setPosition( 80.0f, y );
    mBindingButtons[action]->setText( text );
    mBindingButtons[action]->setToggle( true );

    mBindingLabels[action] = std::make_shared<GUI::Label>( "", *context.fonts );
    mBindingLabels[action]->setPosition( 300.0f, y + 15.0f );

    mGUIContainer.pack( mBindingButtons[action] );
    mGUIContainer.pack( mBindingLabels[action] );
}
