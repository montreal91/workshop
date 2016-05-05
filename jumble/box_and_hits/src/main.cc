
#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>

// #include "src/ih/controller.h"
#include "src/nodes/real_box.h"


/** We need this to easily convert between pixel and real-world coordinates */
static const float SCALE = 30.0f;

// Create the base for the boxes to land
void CreateGround(b2World& World, float X, float Y) {
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
    BodyDef.type = b2_staticBody;
    b2Body* Body = World.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((800.0f / 2) / SCALE, (16.0f / 2) / SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.0f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
}

int main(int argc, char const *argv[]) {
    // Prepare the window
    sf::RenderWindow Window(
        sf::VideoMode(800, 600, 32),
        "SFML & Box2D",
        sf::Style::Fullscreen
    );
    Window.setFramerateLimit(60);

    // Prepare the world
    b2Vec2 Gravity(0.0f, 10.0f);
    b2World World(Gravity);
    CreateGround(World, 400.0f, 500.0f);

    // Prepare textures
    sf::Texture GroundTexture;
    sf::Texture BoxTexture;
    GroundTexture.loadFromFile("media/sprites/ground.png");
    BoxTexture.loadFromFile("media/sprites/box.png");
    nodes::ERealBox box(World, BoxTexture);
    // ih::EKeyBinding binding;
    // ih::EController controller( &binding, 0 );

    while (Window.isOpen()) {
        // ih::ECommandQueue cq;
        sf::Event event;
        while (Window.pollEvent(event)) {
            // controller.HandleEvent(event, cq);
            if (event.type == sf::Event::Closed) {
                Window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                Window.close();
            }
        }
        // controller.HandleRealtimeInput(cq);
        World.Step(1/60.0f, 8, 3);
        box.UpdateFace();

        Window.clear(sf::Color::White);
        for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext()) {
            if (BodyIterator->GetType() == b2_staticBody) {
                sf::Sprite GroundSprite;
                GroundSprite.setTexture(GroundTexture);
                GroundSprite.setOrigin(400.0f, 8.0f);
                GroundSprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
                GroundSprite.setRotation(180/b2_pi * BodyIterator->GetAngle());
                Window.draw(GroundSprite);
            } 
        }
        Window.draw(box);
        Window.display();
    }
    return 0;
}
