
#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>

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

// Create the boxes
void CreateBox(b2World& World, int MouseX, int MouseY) {
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE);
    BodyDef.type = b2_dynamicBody;
    b2Body* Body = World.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((32.0f/2) / SCALE, (32.0f/2)/SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.0f;
    FixtureDef.friction = 0.7f;
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
    b2Vec2 Gravity(0.0f, 9.8f);
    b2World World(Gravity);
    CreateGround(World, 400.0f, 500.0f);

    // Prepare textures
    sf::Texture GroundTexture;
    sf::Texture BoxTexture;
    GroundTexture.loadFromFile("ground.png");
    BoxTexture.loadFromFile("box.png");

    while (Window.isOpen()) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            int MouseX = sf::Mouse::getPosition(Window).x;
            int MouseY = sf::Mouse::getPosition(Window).y;
            CreateBox(World, MouseX, MouseY);
        }
        sf::Event event;
        while (Window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                Window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                Window.close();
            }

        }
        World.Step(1/60.0f, 8, 3);

        Window.clear(sf::Color::White);
        int BodyCount = 0;
        for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext()) {
            if (BodyIterator->GetType() == b2_dynamicBody) {
                sf::Sprite Sprite;
                Sprite.setTexture(BoxTexture);
                Sprite.setOrigin(16.0f, 16.0f);
                Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
                Sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
                Window.draw(Sprite);
                ++BodyCount;
            } else {
                sf::Sprite GroundSprite;
                GroundSprite.setTexture(GroundTexture);
                GroundSprite.setOrigin(400.0f, 8.0f);
                GroundSprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
                GroundSprite.setRotation(180/b2_pi * BodyIterator->GetAngle());
                Window.draw(GroundSprite);
            }
        }
        Window.display();
    }
    return 0;
}
