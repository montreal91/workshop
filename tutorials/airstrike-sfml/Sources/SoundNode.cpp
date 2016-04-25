
#include "SoundNode.hpp"


SoundNode::SoundNode( SoundPlayer& player ) :
SceneNode(),
mSounds( player ) {}

void
SoundNode::playSound( SoundEffect::ID sound, sf::Vector2f position  ) {
    mSounds.play( sound, position );
}

void
SoundNode::playSound( SoundEffect::ID sound ) {
    mSounds.play( sound, sf::Vector2f() );
}

unsigned int
SoundNode::getCategory() const {
    return Category::SoundEffect;
}
