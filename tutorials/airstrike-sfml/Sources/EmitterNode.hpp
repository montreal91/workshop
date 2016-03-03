
#ifndef __EMITTER_NODE_HPP__
#define __EMITTER_NODE_HPP__

#include "SceneNode.hpp"
#include "Particle.hpp"


class ParticleNode;

class EmitterNode : public SceneNode {
public:
    explicit EmitterNode( Particle::Type type );

private:
    // TODO: Add corresponding includes
    virtual void    updateCurrent( sf::Time dt, CommandQueue& commands );
    void            emitParticles( sf::Time dt );

    sf::Time mAccumulatedTime;
    Particle::Type mType;
    ParticleNode* mParticleSystem;
};

#endif // __EMITTER_NODE_HPP__
