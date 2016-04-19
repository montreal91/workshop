
#include <iostream>
#include <cmath>

#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>

const float PIXELS_PER_METER = 100.0f;

void DoSomePhysicMagic(b2Body* body, sf::RectangleShape* shape) {
    b2Vec2 pos = body->GetPosition();
    float32 angle = body->GetAngle();

    shape->setPosition(pos.x*PIXELS_PER_METER, pos.y*PIXELS_PER_METER);
    shape->setRotation(angle);
}

void CenterOrigin(sf::RectangleShape* shape) {
    sf::FloatRect bounds = shape->getLocalBounds();
    shape->setOrigin(
        std::floor( bounds.left + bounds.width / 2.0f ),
        std::floor( bounds.top + bounds.height / 2.0f )
    );
}

int main(int argc, char const *argv[]) {
    sf::RenderWindow window( sf::VideoMode( 600, 600 ), "SFML & BOX2D" );
    sf::RectangleShape body( sf::Vector2f( 120.0f, 90.0f ) );
    sf::RectangleShape ground( sf::Vector2f( 600.0f, 50.0f ) );

    body.setFillColor( sf::Color( 100, 10, 10 ) );
    body.setPosition( 250.0f, 0.0f );
    CenterOrigin(&body);

    ground.setFillColor( sf::Color::Black );
    ground.setPosition(0.0f, 550.0f);
    CenterOrigin(&ground);

    B2_NOT_USED( argc );
    B2_NOT_USED( argv );

    b2Vec2 gravity( 0.0f, 1.5f );

    b2World world( gravity );

    // Create ground
    b2BodyDef ground_body_def;
    ground_body_def.position.Set( 3.0f, 5.9f );

    b2Body* groundBody = world.CreateBody( &ground_body_def );

    b2PolygonShape ground_box;

    ground_box.SetAsBox( 50.0f, 0.1f );

    groundBody->CreateFixture( &ground_box, 0.0f );

    // Create falling box
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    body_def.position.Set( 3.0f, 0.0f );
    b2Body* phys_body = world.CreateBody( &body_def );

    b2MassData m_data;
    phys_body->GetMassData(&m_data);
    m_data.center.Set(0.0f, 0.01f);
    phys_body->SetMassData(&m_data);

    b2PolygonShape dynamic_box;
    dynamic_box.SetAsBox( 1.0f, 0.6f );

    b2FixtureDef fixture_def;
    fixture_def.shape = &dynamic_box;

    fixture_def.density = 1.0f;
    fixture_def.friction = 0.3f;

    phys_body->CreateFixture( &fixture_def );

    float32 time_step = 1.0f / 60.0f;
    int32 velocity_iterations = 6;
    int32 position_iterations = 2;

    sf::Clock clock;
    sf::Time time_since_last_update;

    while ( window.isOpen() ) {
        sf::Time dt = clock.restart();
        time_since_last_update += dt;
        if (time_since_last_update.asSeconds() >= time_step) {
            sf::Event event;
            while ( window.pollEvent( event ) ) {
                if ( event.type == sf::Event::Closed ) {
                    window.close();
                }
            }
            world.Step(time_step, velocity_iterations, position_iterations);
            DoSomePhysicMagic(phys_body, &body);
            DoSomePhysicMagic(groundBody, &ground);
            window.clear( sf::Color( 10, 100, 10 ) );
            window.draw( ground );
            window.draw( body );
            window.display();
            time_since_last_update = sf::seconds(0.0f);
        }
    }
    return 0;
}
