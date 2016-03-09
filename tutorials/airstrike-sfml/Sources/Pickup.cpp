
#include "Pickup.hpp"


namespace {
const std::vector<PickupData> Table = initalizePickupData();
} // namespace

Pickup::Pickup( Type type, const TextureHolder& textures ) :
Entity( 1 ),
mType( type ),
mSprite( textures.get( Table[type].texture ), Table[type].textureRect ) {
    centerOrigin( mSprite );
}

unsigned int
Pickup::GetCategory() const {
    return Category::Pickup;
}

sf::FloatRect
Pickup::GetBoundingRect() const {
    return GetWorldTransform().transformRect( mSprite.getGlobalBounds() );
}

void
Pickup::Apply( Aircraft& player ) const {
    Table[mType].action( player );
}

void
Pickup::DrawCurrent(
    sf::RenderTarget& target,
    sf::RenderStates states
) const {
    target.draw( mSprite, states );
}
