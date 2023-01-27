
use bevy::prelude::*;


#[derive(Component)]
struct Person;


#[derive(Component)]
struct Name(String);

#[derive(Resource)]
struct GreetTimer(Timer);


fn add_people(mut commands: Commands) {
    commands.spawn((Person, Name("Elaina Proctor".to_string())));
    commands.spawn((Person, Name("Renzo Hume".to_string())));
    commands.spawn((Person, Name("Zayna Nieves".to_string())));
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
        let timer = GreetTimer(
            Timer::from_seconds(2.0, TimerMode::Repeating)
        );
        app.insert_resource(timer)
            .add_startup_system(add_people)
            .add_system(greet_people);
    }
}
