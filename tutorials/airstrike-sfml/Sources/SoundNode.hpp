
#pragma once


#include <SFML/System/Vector2.hpp>

#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SoundPlayer.hpp"


class SoundNode : public SceneNode {
public:
    explicit SoundNode( SoundPlayer& player );

    void                    playSound(
        SoundEffect::ID sound,
        sf::Vector2f position
    );
    void playSound( SoundEffect::ID sound );

    virtual unsigned int    getCategory() const;

private:
    SoundPlayer& mSounds;
};
