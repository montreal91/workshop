
use bevy::prelude::*;

const TEXT_COLOR: Color = Color::rgb(0.9, 0.9, 0.9);

#[derive(Clone, Eq, PartialEq, Debug, Hash)]
enum GameState {
    Splash,
    Menu,
    Game,
}

#[derive(Resource, Debug, Component, PartialEq, Clone, Copy)]
enum DisplayQuality {
    Low,
    Medium,
    High,
}

#[derive(Resource, Debug, Component, PartialEq, Clone, Copy)]
struct Volume(u32);

fn main() {
    App::new()
        .add_plugins(DefaultPlugins)
        .insert_resource(DisplayQuality::Medium)
        .insert_resource(Volume(7))
        .add_startup_system(setup)
        .add_state(GameState::Splash)
        .add_plugin(splash::SplashPlugin)
        .add_plugin(menu::MenuPlugin)
        .add_plugin(game::GamePlugin)
        .run();
}

fn setup(mut commands: Commands) {
    commands.spawn(Camera2dBundle::default());
}

mod splash {

    use bevy::prelude::*;

    use super::{
        despawn_screen,
        GameState
    };

    pub struct SplashPlugin;

    impl Plugin for SplashPlugin {
        fn build(&self, app: &mut App) {
            app.add_system_set(SystemSet::on_enter(GameState::Splash).with_system(splash_setup))
                .add_system_set(SystemSet::on_update(GameState::Splash).with_system(countdown))
                .add_system_set(SystemSet::on_exit(GameState::Splash).with_system(despawn_screen::<OnSplashScreen>));
        }
    }

    #[derive(Component)]
    struct OnSplashScreen;


    #[derive(Resource, Deref, DerefMut)]
    struct SplashTimer(Timer);


    fn splash_setup(mut commands: Commands, asset_server: Res<AssetServer>) {
        println!("Splash Setup System");
        let icon = asset_server.load("branding/icon.png");

        commands.spawn((
            ImageBundle {
                style: Style {
                    margin: UiRect::all(Val::Auto),
                    size: Size::new(Val::Px(200.0), Val::Auto),
                    ..default()
                },
                image: UiImage(icon),
                ..default()
            },
            OnSplashScreen,
        ));

        commands.insert_resource(SplashTimer(Timer::from_seconds(1.0, TimerMode::Once)));
    }

    fn countdown(mut game_state: ResMut<State<GameState>>, time: Res<Time>, mut timer: ResMut<SplashTimer>) {
        if timer.tick(time.delta()).finished() {
            game_state.set(GameState::Menu).unwrap();
        }
    }
}

mod game {
    use bevy::prelude::*;

    use super::{
        despawn_screen,
        DisplayQuality,
        GameState,
        Volume,
        TEXT_COLOR,
    };

    pub struct GamePlugin;

    impl Plugin for GamePlugin {
        fn build(&self, app: &mut App) {
            app.add_system_set(SystemSet::on_enter(GameState::Game).with_system(game_setup))
                .add_system_set(SystemSet::on_update(GameState::Game).with_system(game))
                .add_system_set(SystemSet::on_exit(GameState::Game).with_system(despawn_screen::<OnGameScreen>))
            ;
        }
    }

    #[derive(Component)]
    struct OnGameScreen;

    #[derive(Resource, Deref, DerefMut)]
    struct GameTimer(Timer);

    fn game_setup(
        mut commands: Commands,
        asset_server: Res<AssetServer>,
        display_quality: Res<DisplayQuality>,
        volume: Res<Volume>
    ) {
        println!("Game Setup System");
        let font = asset_server.load("fonts/FiraSans-Bold.ttf");
        commands.spawn((NodeBundle {
            style: Style {
                margin: UiRect::all(Val::Auto),
                flex_direction: FlexDirection::Column,
                align_items: AlignItems::Center,
                ..default()
            },
            background_color: Color::BLACK.into(),
            ..default()
        },
        OnGameScreen,
        ))
        .with_children(|parent| {
            parent.spawn(
                TextBundle::from_section(
                    "Will be back to the menu shortly...",
                    TextStyle {
                        font: font.clone(),
                        font_size: 80.0,
                        color: TEXT_COLOR,
                    },
                )
                .with_style(
                    Style {
                        margin: UiRect::all(Val::Px(50.0)),
                        ..default()
                    }
                )
            );
            parent.spawn(
                TextBundle::from_sections([
                    TextSection::new(
                        format!("quality: {:?}", *display_quality),
                        TextStyle {
                            font: font.clone(),
                            font_size: 60.0,
                            color: Color::BLUE,
                        }
                    ),
                    TextSection::new(
                        " - ",
                        TextStyle {
                            font: font.clone(),
                            font_size: 60.0,
                            color: TEXT_COLOR,
                        }
                    ),
                    TextSection::new(
                        format!("volume: {:?}", *volume),
                        TextStyle {
                            font: font.clone(),
                            font_size: 60.0,
                            color: Color::GREEN,
                        }
                    ),
                ])
                .with_style(Style {
                    margin: UiRect::all(Val::Px(50.0)),
                    ..default()
                }),
            );
        });
        commands.insert_resource(GameTimer(Timer::from_seconds(5.0, TimerMode::Once)));
    }

    fn game(
        time: Res<Time>,
        mut game_state: ResMut<State<GameState>>,
        mut timer: ResMut<GameTimer>,
    ) {
        if timer.tick(time.delta()).finished() {
            game_state.set(GameState::Menu).unwrap();
        }
    }
}

mod menu {
    use bevy::prelude::*;
    use bevy::app::AppExit;

    use super::{
        despawn_screen,
        DisplayQuality,
        GameState,
        Volume,
        TEXT_COLOR,
    };

    pub struct MenuPlugin;

    impl Plugin for MenuPlugin {
        fn build(&self, app: &mut App) {
            app.add_state(MenuState::Disabled);
            app.add_system_set(SystemSet::on_enter(GameState::Menu).with_system(menu_setup));
            app.add_system_set(SystemSet::on_enter(MenuState::Main).with_system(main_menu_setup));
            app.add_system_set(SystemSet::on_exit(MenuState::Main).with_system(despawn_screen::<OnMainMenuScreen>));

            app.add_system_set(SystemSet::on_enter(MenuState::Settings).with_system(settings_menu_setup));
            app.add_system_set(SystemSet::on_exit(MenuState::Settings).with_system(despawn_screen::<OnSettingsMenuScreen>));

            // Systems to handle the display settings screen
            app.add_system_set(SystemSet::on_enter(MenuState::SettingsDisplay).with_system(display_settings_menu_setup));
            app.add_system_set(SystemSet::on_update(MenuState::SettingsDisplay).with_system(setting_button::<DisplayQuality>));
            app.add_system_set(SystemSet::on_exit(MenuState::SettingsDisplay).with_system(despawn_screen::<OnDisplaySettingsMenuScreen>));

            // Systems to handle the sound settings screen
            app.add_system_set(SystemSet::on_enter(MenuState::SettingsSound).with_system(sound_settings_menu_setup));
            app.add_system_set(SystemSet::on_update(MenuState::SettingsSound).with_system(setting_button::<Volume>));
            app.add_system_set(SystemSet::on_exit(MenuState::SettingsSound).with_system(despawn_screen::<OnSoundSettingsMenuScreen>));

            // Common systems to all screens that handles buttons behaviour
            app.add_system_set(
                SystemSet::on_update(GameState::Menu).with_system(menu_action).with_system(button_system),
            );
        }
    }

    #[derive(Clone, Eq, PartialEq, Debug, Hash)]
    enum MenuState {
        Main,
        Settings,
        SettingsDisplay,
        SettingsSound,
        Disabled,
    }

    #[derive(Component)]
    struct OnMainMenuScreen;

    #[derive(Component)]
    struct OnSettingsMenuScreen;

    #[derive(Component)]
    struct OnDisplaySettingsMenuScreen;

    #[derive(Component)]
    struct OnSoundSettingsMenuScreen;

    const NORMAL_BUTTON: Color = Color::rgb(0.15, 0.15, 0.15);
    const HOVERED_BUTTON: Color = Color::rgb(0.25, 0.25, 0.25);
    const HOVERED_PRESSED_BUTTON: Color = Color::rgb(0.25, 0.65, 0.25);
    const PRESSED_BUTTON: Color = Color::rgb(0.35, 0.75, 0.35);

    #[derive(Component)]
    struct SelectedOption;

    #[derive(Component)]
    enum MenuButtonAction {
        Play,
        Settings,
        SettingsDisplay,
        SettingsSound,
        BackToMainMenu,
        BackToSettings,
        Quit,
    }

    // This system handles changing all buttons color based on mouse interaction
    fn button_system(
        mut interaction_query:
            Query<(&Interaction, &mut BackgroundColor, Option<&SelectedOption>), (Changed<Interaction>, With<Button>)>
        ) {

        for (interaction, mut color, selected) in &mut interaction_query {
            *color = match (*interaction, selected) {
                (Interaction::Clicked, _) | (Interaction::None, Some(_)) => PRESSED_BUTTON.into(),
                (Interaction::Hovered, Some(_)) => HOVERED_PRESSED_BUTTON.into(),
                (Interaction::Hovered, None) => HOVERED_BUTTON.into(),
                (Interaction::None, None) => NORMAL_BUTTON.into(),
            }
        }
    }


    // This system updates the settings when a new value for a setting is selected, and marks
    // the button as the one currently selected
    fn setting_button<T: Resource + Component + PartialEq + Copy>(
        interaction_query: Query<(&Interaction, &T, Entity), (Changed<Interaction>, With<Button>)>,
        mut selected_query: Query<(Entity, &mut BackgroundColor), With<SelectedOption>>,
        mut commands: Commands,
        mut setting: ResMut<T>
    ) {
        for (interaction, button_setting, entity) in &interaction_query {
            if *interaction == Interaction::Clicked && *setting != *button_setting {
                let (previous_button, mut previous_color) = selected_query.single_mut();
                *previous_color = NORMAL_BUTTON.into();
                commands.entity(previous_button).remove::<SelectedOption>();
                commands.entity(entity).insert(SelectedOption);
                *setting = *button_setting;
            }
        }
    }

    fn menu_setup(mut menu_state: ResMut<State<MenuState>>) {
        println!("Menu Setup System");
        let _ = menu_state.set(MenuState::Main);
    }

    fn main_menu_setup(mut commands: Commands, asset_server: Res<AssetServer>) {
        println!("Main Menu Setup System");
        let font = asset_server.load("fonts/FiraSans-Bold.ttf");
        let button_style = Style {
            size: Size::new(Val::Px(250.0), Val::Px(65.0)),
            margin: UiRect::all(Val::Px(20.0)),
            justify_content: JustifyContent::Center,
            align_items: AlignItems::Center,
            ..default()
        };

        let button_icon_style = Style {
            size: Size::new(Val::Px(30.0), Val::Auto),
            position_type: PositionType::Absolute,
            position: UiRect { left: Val::Px(10.0), right: Val::Auto, top: Val::Auto, bottom: Val::Auto },
            ..default()
        };

        let button_text_style = TextStyle {
            font: font.clone(),
            font_size: 40.0,
            color: TEXT_COLOR
        };

        commands.spawn((
            NodeBundle {
                style: Style {
                    margin: UiRect::all(Val::Auto),
                    flex_direction: FlexDirection::Column,
                    align_items: AlignItems::Center,
                    ..default()
                },
                ..default()
            },
            OnMainMenuScreen
        )).with_children(|parent| {
            // Display the game name
            parent.spawn(
                TextBundle::from_section(
                    "Bevy Game Menu UI",
                    TextStyle {
                        font: font.clone(),
                        font_size: 80.0,
                        color: TEXT_COLOR
                    }
                ).with_style(
                    Style {
                        margin: UiRect::all(Val::Px(50.0)),
                        ..default()
                    }
                )
            );

            // Display three buttons for each action available from the main menu:
            // - new game
            // - settings
            // - quit
            parent.spawn((
                ButtonBundle {
                    style: button_style.clone(),
                    background_color: NORMAL_BUTTON.into(),
                    ..default()
                },
                MenuButtonAction::Play
            )).with_children(|parent| {
                let icon = asset_server.load("textures/right.png");

                parent.spawn(
                    ImageBundle {
                        style: button_icon_style.clone(),
                        image: UiImage(icon),
                        ..default()
                    }
                );

                parent.spawn(
                    TextBundle::from_section(
                        "New Game",
                        button_text_style.clone(),
                    )
                );
            });

            // Settings
            parent.spawn((
                ButtonBundle {
                    style: button_style.clone(),
                    background_color: NORMAL_BUTTON.into(),
                    ..default()
                },
                MenuButtonAction::Settings,
            )).with_children(|parent| {
                let icon = asset_server.load("textures/wrench.png");
                parent.spawn(
                    ImageBundle {
                        style: button_icon_style.clone(),
                        image: UiImage(icon),
                        ..default()
                    }
                );
                parent.spawn(
                    TextBundle::from_section("Settings", button_text_style.clone())
                );
            });

            // Quit
            parent.spawn((
                ButtonBundle {
                    style: button_style,
                    background_color: NORMAL_BUTTON.into(),
                    ..default()
                },
                MenuButtonAction::Quit,
            )).with_children(|parent| {
                let icon = asset_server.load("textures/exitRight.png");

                parent.spawn(
                    ImageBundle {
                        style: button_icon_style,
                        image: UiImage(icon),
                        ..default()
                    }
                );

                parent.spawn(
                    TextBundle::from_section("Quit", button_text_style)
                );
            });
        });
    }

    fn settings_menu_setup(mut commands: Commands, asset_server: Res<AssetServer>) {
        println!("Settings Menu System");

        let button_style = Style {
            size: Size::new(Val::Px(200.0), Val::Px(65.0)),
            margin: UiRect::all(Val::Px(20.0)),
            justify_content: JustifyContent::Center,
            align_items: AlignItems::Center,
            ..default()
        };

        let button_text_style = TextStyle {
            font: asset_server.load("fonts/FiraSans-Bold.ttf"),
            font_size: 40.0,
            color: TEXT_COLOR,
        };

        commands.spawn((
            NodeBundle {
                style: Style {
                    margin: UiRect::all(Val::Auto),
                    flex_direction: FlexDirection::Column,
                    align_items: AlignItems::Center,
                    ..default()
                },
                background_color: Color::CRIMSON.into(),
                ..default()
            },
            OnSettingsMenuScreen,
        )).with_children(|parent| {
            let actions = [
                (MenuButtonAction::SettingsDisplay, "Display"),
                (MenuButtonAction::SettingsSound, "Sound"),
                (MenuButtonAction::BackToMainMenu, "Back"),
            ];

            for (action, text) in actions {
                parent.spawn((
                    ButtonBundle {
                        style: button_style.clone(),
                        background_color: NORMAL_BUTTON.into(),
                        ..default()
                    },
                    action,
                )).with_children(|parent| {
                    parent.spawn(TextBundle::from_section(text, button_text_style.clone()));
                });
            }
        });
    }

    fn display_settings_menu_setup(
        mut commands: Commands,
        asset_server: Res<AssetServer>,
        display_quality: Res<DisplayQuality>,
    ) {
        println!("Display Settings Menu System");

        let button_style = Style {
            size: Size::new(Val::Px(200.0), Val::Px(65.0)),
            margin: UiRect::all(Val::Px(20.0)),
            justify_content: JustifyContent::Center,
            align_items: AlignItems::Center,
            ..default()
        };
        let button_text_style = TextStyle {
            font: asset_server.load("fonts/FiraSans-Bold.ttf"),
            font_size: 40.0,
            color: TEXT_COLOR,
        };

        commands
            .spawn((
                NodeBundle {
                    style: Style {
                        margin: UiRect::all(Val::Auto),
                        flex_direction: FlexDirection::Column,
                        align_items: AlignItems::Center,
                        ..default()
                    },
                    background_color: Color::CRIMSON.into(),
                    ..default()
                },
                OnDisplaySettingsMenuScreen,
            ))
            .with_children(|parent| {
                // Create a new `NodeBundle`, this time not setting its `flex_direction`. It will
                // use the default value, `FlexDirection::Row`, from left to right.
                parent
                    .spawn(NodeBundle {
                        style: Style {
                            align_items: AlignItems::Center,
                            ..default()
                        },
                        background_color: Color::CRIMSON.into(),
                        ..default()
                    })
                    .with_children(|parent| {
                        // Display a label for the current setting
                        parent.spawn(TextBundle::from_section(
                            "Display Quality",
                            button_text_style.clone(),
                        ));
                        // Display a button for each possible value
                        for quality_setting in [
                            DisplayQuality::Low,
                            DisplayQuality::Medium,
                            DisplayQuality::High,
                        ] {
                            let mut entity = parent.spawn(ButtonBundle {
                                style: Style {
                                    size: Size::new(Val::Px(150.0), Val::Px(65.0)),
                                    ..button_style.clone()
                                },
                                background_color: NORMAL_BUTTON.into(),
                                ..default()
                            });
                            entity.insert(quality_setting).with_children(|parent| {
                                parent.spawn(TextBundle::from_section(
                                    format!("{quality_setting:?}"),
                                    button_text_style.clone(),
                                ));
                            });
                            if *display_quality == quality_setting {
                                entity.insert(SelectedOption);
                            }
                        }
                    });
                // Display the back button to return to the settings screen
                parent
                    .spawn((
                        ButtonBundle {
                            style: button_style,
                            background_color: NORMAL_BUTTON.into(),
                            ..default()
                        },
                        MenuButtonAction::BackToSettings,
                    ))
                    .with_children(|parent| {
                        parent.spawn(TextBundle::from_section("Back", button_text_style));
                    });
            });
    }

    fn sound_settings_menu_setup(
        mut commands: Commands,
        asset_server: Res<AssetServer>,
        volume: Res<Volume>,
    ) {
        println!("Sound Settings Menu System");

        let button_style = Style {
            size: Size::new(Val::Px(200.0), Val::Px(65.0)),
            margin: UiRect::all(Val::Px(20.0)),
            justify_content: JustifyContent::Center,
            align_items: AlignItems::Center,
            ..default()
        };
        let button_text_style = TextStyle {
            font: asset_server.load("fonts/FiraSans-Bold.ttf"),
            font_size: 40.0,
            color: TEXT_COLOR,
        };

        commands
            .spawn((
                NodeBundle {
                    style: Style {
                        margin: UiRect::all(Val::Auto),
                        flex_direction: FlexDirection::Column,
                        align_items: AlignItems::Center,
                        ..default()
                    },
                    background_color: Color::CRIMSON.into(),
                    ..default()
                },
                OnSoundSettingsMenuScreen,
            ))
            .with_children(|parent| {
                parent
                    .spawn(NodeBundle {
                        style: Style {
                            align_items: AlignItems::Center,
                            ..default()
                        },
                        background_color: Color::CRIMSON.into(),
                        ..default()
                    })
                    .with_children(|parent| {
                        parent.spawn(TextBundle::from_section(
                            "Volume",
                            button_text_style.clone(),
                        ));
                        for volume_setting in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9] {
                            let mut entity = parent.spawn(ButtonBundle {
                                style: Style {
                                    size: Size::new(Val::Px(30.0), Val::Px(65.0)),
                                    ..button_style.clone()
                                },
                                background_color: NORMAL_BUTTON.into(),
                                ..default()
                            });
                            entity.insert(Volume(volume_setting));
                            if *volume == Volume(volume_setting) {
                                entity.insert(SelectedOption);
                            }
                        }
                    });
                parent
                    .spawn((
                        ButtonBundle {
                            style: button_style,
                            background_color: NORMAL_BUTTON.into(),
                            ..default()
                        },
                        MenuButtonAction::BackToSettings,
                    ))
                    .with_children(|parent| {
                        parent.spawn(TextBundle::from_section("Back", button_text_style));
                    });
            });
    }

    fn menu_action(
        interaction_query: Query<(&Interaction, &MenuButtonAction), (Changed<Interaction>, With<Button>)>,
        mut app_exit_events: EventWriter<AppExit>,
        mut menu_state: ResMut<State<MenuState>>,
        mut game_state: ResMut<State<GameState>>
    ) {
        for (interaction, menu_button_action) in &interaction_query {
            if *interaction == Interaction::Clicked {
                match menu_button_action {
                    MenuButtonAction::Quit => {
                        println!("Quitting from the application.");
                        app_exit_events.send(AppExit);
                    }

                    MenuButtonAction::Play => {
                        println!("Play!");
                        game_state.set(GameState::Game).unwrap();
                        menu_state.set(MenuState::Disabled).unwrap();
                    }

                    MenuButtonAction::Settings => {
                        println!("Settings.");
                        menu_state.set(MenuState::Settings).unwrap();
                    }

                    MenuButtonAction::SettingsDisplay => {
                        println!("Settings Display.");
                        menu_state.set(MenuState::SettingsDisplay).unwrap();
                    }

                    MenuButtonAction::SettingsSound => {
                        println!("Settings Sound.");
                        menu_state.set(MenuState::SettingsSound).unwrap();
                    }

                    MenuButtonAction::BackToMainMenu => {
                        println!("Return back to Main Menu.");
                        menu_state.set(MenuState::Main).unwrap();
                    }

                    MenuButtonAction::BackToSettings => {
                        println!("Return back to Settings");
                        menu_state.set(MenuState::Main).unwrap();
                    }
                }
            }
        }
    }
}

fn despawn_screen<T: Component>(to_despawn: Query<Entity, With<T>>, mut commands: Commands) {
    for entity in &to_despawn {
        commands.entity(entity)
            .despawn_recursive();
    }
}
