
#ifndef __STATE_HPP__
#define __STATE_HPP__


#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>


// TODO: replace it with a proper input
namespace sf {
class RenderWindow;
} // namespace sf

class StateStack;
class MusicPlayer;
class SoundPlayer;
class KeyBinding;


class State {
public:
    typedef std::unique_ptr<State> Ptr;

    // TODO: turn context into a class
    struct Context {
        Context(
            sf::RenderWindow& window,
            TextureHolder& textures,
            FontHolder& fonts,
            MusicPlayer& music,
            SoundPlayer& sounds,
            KeyBinding& keys1,
            KeyBinding& keys2
        );

        sf::RenderWindow*   window;
        TextureHolder*      textures;
        FontHolder*         fonts;
        MusicPlayer*        music;
        SoundPlayer*        sounds;
        KeyBinding*         keys1;
        KeyBinding*         keys2;
    };

    State( StateStack& stack, Context context );
    virtual         ~State();

    virtual void    draw() = 0;
    virtual bool    update( sf::Time dt ) = 0;
    virtual bool    handleEvent( const sf::Event& event ) = 0;

    virtual void    onActivate();
    virtual void    onDestroy();

protected:
    void    requestStackPush( States::ID stateID );
    void    requestStackPop();
    void    requestStateClear();

    Context getContext() const;

private:
    StateStack* mStack;
    Context     mContext;
};

#endif // __STATE_HPP__
