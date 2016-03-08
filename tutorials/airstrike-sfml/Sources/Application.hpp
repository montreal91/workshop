
#pragma once

#include <string>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "GameOverState.hpp"
#include "GameState.hpp"
#include "MenuState.hpp"
#include "MultiplayerGameState.hpp"
#include "MusicPlayer.hpp"
#include "KeyBinding.hpp"
#include "PauseState.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SettingsState.hpp"
#include "SoundPlayer.hpp"
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "StateStack.hpp"
#include "TitleState.hpp"
#include "Utility.hpp"


class Application {
public:
    Application();
    
    void run();

private:
    void processInput();
    void update( sf::Time dt );
    void render();

    void updateStatistics( sf::Time dt );
    void registerStates();

    static const sf::Time   TimePerFrame;

    sf::RenderWindow        mWindow;
    TextureHolder           mTextures;
    FontHolder              mFonts;
    MusicPlayer             mMusic;
    SoundPlayer             mSounds;

    KeyBinding              mKeyBinding1;
    KeyBinding              mKeyBinding2;
    StateStack              mStateStack;

    sf::Text                mStatisticsText;
    sf::Time                mStatisticsUpdateTime;
    std::size_t             mStatisticsNumFrames;
};
