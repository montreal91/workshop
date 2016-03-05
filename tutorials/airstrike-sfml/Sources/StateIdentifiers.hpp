
#ifndef __STATE_IDENTIFIERS_HPP__
#define __STATE_IDENTIFIERS_HPP__


namespace States {
enum ID {
    None,
    Title,
    Menu,
    Game,
    Loading,
    Pause,
    NetworkPause,
    Settings,
    GameOver,
    MissionSuccess,
    HostGame,
    JoinGame,
};

} // namespace States

#endif // __STATE_IDENTIFIERS_HPP__
