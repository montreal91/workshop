
#pragma once


#include <algorithm>
#include <deque>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "DataTables.hpp"
#include "Particle.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"


class ParticleNode : public SceneNode {
public:
    ParticleNode( Particle::Type type, const TextureHolder& textures );

    void                    AddParticle( sf::Vector2f position );
    Particle::Type          GetParticleType() const;
    virtual unsigned int    GetCategory() const;

private:
    virtual void    UpdateCurrent( sf::Time dt, CommandQueue& commands );
    virtual void    DrawCurrent(
        sf::RenderTarget& target, sf::RenderStates states
    ) const;

    void            AddVertex(
        float worldX,
        float worldY,
        float texCoordX,
        float texCoordY,
        const sf::Color& color
    ) const;
    void            ComputeVertices() const;

    std::deque<Particle>    mParticles;
    const sf::Texture&      mTexture;
    Particle::Type          mType;

    mutable sf::VertexArray mVertexArray;
    mutable bool            mNeedsVertexUpdate;
};
