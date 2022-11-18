
use bevy::prelude::App;
use bevy::prelude::DefaultPlugins;

use my_bevy_game::HelloPlugin;


fn main() {
    App::new()
        .add_plugins(DefaultPlugins)
        .add_plugin(HelloPlugin)
        .run();
}
