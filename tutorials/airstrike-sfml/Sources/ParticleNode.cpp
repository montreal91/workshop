
#include "ParticleNode.hpp"


namespace {
const std::vector<ParticleData> Table = initalizeParticleData();
} // namespace

ParticleNode::ParticleNode(
    Particle::Type type,
    const TextureHolder& textures ) :
SceneNode(),
mParticles(),
mTexture( textures.get( Textures::Particle ) ),
mType( type ),
mVertexArray( sf::Quads ),
mNeedsVertexUpdate( true ) {}

void
ParticleNode::AddParticle( sf::Vector2f position ) {
    Particle particle;
    particle.position = position;
    particle.color = Table[mType].color;
    particle.lifetime = Table[mType].lifetime;

    mParticles.push_back( particle );
}

Particle::Type
ParticleNode::GetParticleType() const {
    return mType;
}

unsigned int
ParticleNode::GetCategory() const {
    return Category::ParticleSystem;
}

void
ParticleNode::UpdateCurrent( sf::Time dt, CommandQueue& ) {
    // Remove expired particles
    while ( !mParticles.empty() && mParticles.front().lifetime <= sf::Time::Zero ) {
        mParticles.pop_front();
    }

    // Decrease lifetime of existing particles
    for ( Particle& particle : mParticles ) {
        particle.lifetime -= dt;
    }
    mNeedsVertexUpdate = true;
}

void
ParticleNode::DrawCurrent(
    sf::RenderTarget& target, sf::RenderStates states
) const {
    if ( mNeedsVertexUpdate ) {
        ComputeVertices();
        mNeedsVertexUpdate = false;
    }
    states.texture = &mTexture;

    target.draw( mVertexArray, states );
}

void
ParticleNode::AddVertex(
    float worldX,
    float worldY,
    float texCoordX,
    float texCoordY,
    const sf::Color& color
) const {
    sf::Vertex vertex;
    vertex.position     = sf::Vector2f( worldX, worldY );
    vertex.texCoords    = sf::Vector2f( texCoordX, texCoordY );
    vertex.color        = color;

    mVertexArray.append( vertex );
}

void
ParticleNode::ComputeVertices() const {
    sf::Vector2f size( mTexture.getSize() );
    sf::Vector2f half = size / 2.0f;

    mVertexArray.clear();
    for ( const Particle& particle : mParticles ) {
        sf::Vector2f pos    = particle.position;
        sf::Color color     = particle.color;

        float ratio = particle.lifetime.asSeconds() / Table[mType].lifetime.asSeconds();
        color.a = static_cast<sf::Uint8>( 255 * std::max( ratio, 0.0f ) );

        AddVertex( pos.x - half.x, pos.y - half.y, 0.0f, 0.0f, color );
        AddVertex( pos.x + half.x, pos.y - half.y, size.x, 0.0f, color );
        AddVertex( pos.x + half.x, pos.y + half.y, size.x, size.y, color );
        AddVertex( pos.x - half.x, pos.y + half.y, 0.0f, size.y, color );
    }
}
