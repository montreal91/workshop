
#include "EmitterNode.hpp"


EmitterNode::EmitterNode( Particle::Type type ):
SceneNode(),
mAccumulatedTime( sf::Time::Zero ),
mType( type ),
mParticleSystem( nullptr ) {}

void
EmitterNode::UpdateCurrent( sf::Time dt, CommandQueue& commands ) {
    if ( mParticleSystem ) {
        EmitParticles( dt );
    } else {
        // Find particle node with the same type as emitter node
        auto finder = [this](ParticleNode& container, sf::Time ) {
            if ( container.GetParticleType() == mType ) {
                mParticleSystem = &container;
            }
        };

        Command command;
        command.category = Category::ParticleSystem;
        command.action = derivedAction<ParticleNode>( finder );

        commands.push( command );
    }
}

void
EmitterNode::EmitParticles( sf::Time dt ) {
    const float emissionRate    = 30.0f;
    const sf::Time interval     = sf::seconds( 1.0f ) / emissionRate;

    mAccumulatedTime += dt;

    while ( mAccumulatedTime > interval ) {
        mAccumulatedTime -= interval;
        mParticleSystem->AddParticle( GetWorldPosition() );
    }
}
