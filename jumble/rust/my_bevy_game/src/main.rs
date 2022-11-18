use bevy::prelude::*;


#[derive(Component)]
struct Person;


#[derive(Component)]
struct Name(String);

#[derive(Default)]
struct GreetTimer(Timer);


fn add_people(mut commands: Commands) {
    commands.spawn().insert_bundle((Person, Name("Elaina Proctor".to_string())));
    commands.spawn().insert_bundle((Person, Name("Renzo Hume".to_string())));
    commands.spawn().insert_bundle((Person, Name("Zayna Nieves".to_string())));
}


fn print_greetings(query: Query<&Name, With<Person>>) {
    for name in query.iter() {
        println!("hello {}!", name.0);
    }
    println!();
}


fn greet_people(
    time: Res<Time>,
    mut timer: ResMut<GreetTimer>,
    query: Query<&Name, With<Person>>
) {
    if timer.0.tick(time.delta()).just_finished() {
        print_greetings(query);
    }
}


pub struct HelloPlugin;


impl Plugin for HelloPlugin {
    fn build(&self, app: &mut App) {
        app.insert_resource(GreetTimer(Timer::from_seconds(2.0, true)))
            .add_startup_system(add_people)
            .add_system(greet_people);
    }
}


fn main() {
    App::new()
        .add_plugins(DefaultPlugins)
        .add_plugin(HelloPlugin)
        .run();
}
