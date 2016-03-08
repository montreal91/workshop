
#pragma once


#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/NonCopyable.hpp>


class PostEffect : sf::NonCopyable {
public:
    virtual ~PostEffect();

    virtual void    apply(
        const sf::RenderTexture& input,
        sf::RenderTarget& output
    ) = 0;

    static bool     isSupported();

protected:
    static void     applyShader(
        const sf::Shader& shader,
        sf::RenderTarget& output
    );
};
