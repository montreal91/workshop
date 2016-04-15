
#include <Box2D/Box2D.h>

#include <stdio.h>

int main(int argc, char const *argv[]) {
    B2_NOT_USED( argc );
    B2_NOT_USED( argv );

    b2Vec2 gravity( 0.0f, -10.0f );

    b2World world( gravity );
    b2BodyDef ground_body_def;
    ground_body_def.position.Set( 0.0f, -10.0f );

    b2Body* groundBody = world.CreateBody( &ground_body_def );

    b2PolygonShape ground_box;

    ground_box.SetAsBox( 50.0f, 10.0f );

    groundBody->CreateFixture( &ground_box, 0.0f );

    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    body_def.position.Set( 0.0f, 4.0f );
    b2Body* body = world.CreateBody( &body_def );

    b2PolygonShape dynamic_box;
    dynamic_box.SetAsBox( 1.0f, 1.0f );

    b2FixtureDef fixture_def;
    fixture_def.shape = &dynamic_box;

    fixture_def.density = 1.0f;
    fixture_def.friction = 0.3f;

    body->CreateFixture( &fixture_def );

    float32 time_step = 1.0f / 60.0f;
    int32 velocity_iterations = 6;
    int32 position_iterations = 2;

    for ( int32 i = 0; i < 60; i++ ) {
        world.Step( time_step, velocity_iterations, position_iterations );

        b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();

        printf( "%4.2f %4.2f %4.2f\n", position.x, position.y, angle );
    }
    return 0;
}
