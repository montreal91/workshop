
#ifndef __POST_EFFECT_HPP__
#define __POST_EFFECT_HPP__

#include <SFML/System/NonCopyable.hpp>

// TODO: Replace this ugliness with proper input
namespace sf {
class RenderTarget;
class RenderTexture;
class Shader;
} // namespace sf

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

#endif // __POST_EFFECT_HPP__
