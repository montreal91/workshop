
#pragma once


#include <SFML/System/Time.hpp>

#include "Command.hpp"
#include "CommandQueue.hpp"
#include "Particle.hpp"
#include "ParticleNode.hpp"
#include "SceneNode.hpp"


class EmitterNode : public SceneNode {
public:
    explicit EmitterNode( Particle::Type type );

private:
    virtual void    UpdateCurrent( sf::Time dt, CommandQueue& commands );
    void            EmitParticles( sf::Time dt );

    sf::Time        mAccumulatedTime;
    Particle::Type  mType;
    ParticleNode*   mParticleSystem;
};
