
#ifndef __SOUND_NODE_HPP__
#define __SOUND_NODE_HPP__


#include "SceneNode.hpp"
#include "ResourceIdentifiers.hpp"


// TODO: replace this with a proper input
class SoundPlayer;

class SoundNode : public SceneNode {
public:
    explicit SoundNode( SoundPlayer& player );

    void                    playSound(
        SoundEffect::ID sound,
        sf::Vector2f position
    );

    virtual unsigned int    getCategory() const;

private:
    SoundPlayer& mSounds;
};

#endif // __SOUND_NODE_HPP__
