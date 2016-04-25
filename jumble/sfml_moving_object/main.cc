
#include <cmath>

#include <SFML/Graphics.hpp>

void CenterOrigin(sf::Sprite* sprite) {
    sf::FloatRect bounds = sprite->getLocalBounds();
    sprite->setOrigin(
        std::floor( bounds.left + bounds.width / 2.0f ),
        std::floor( bounds.top + bounds.height / 2.0f )
    );
}

float GetLength( const sf::Vector2f& vec ) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f Normalize(const sf::Vector2f& vec) {
    float length = GetLength(vec);
    return sf::Vector2f(vec.x / length, vec.y / length);
}


sf::Vector2f GetDirection(const sf::Vector2f& start, const sf::Vector2f& destination) {
    sf::Vector2f dir = destination - start;
    if (GetLength(dir) <= 0.1) {
        return sf::Vector2f(0.0f, 0.0f);
    }
    return Normalize(dir);
}

float
RadianToDegree( float radian ) {
    return 180.0f / M_PI * radian;
}

void UpdateSprite(
    sf::Sprite* sprite,
    const sf::Vector2f& destination,
    const sf::Time& dt,
    const float speed
) {
    sf::Vector2f pos = sprite->getPosition();
    sf::Vector2f velocity = GetDirection(pos, destination);
    pos += speed * dt.asSeconds() * velocity;

    float angle = std::atan2( velocity.y, velocity.x );
    sprite->setPosition(pos);
    if (GetLength(velocity) > 0.01){
        sprite->setRotation(RadianToDegree(angle) + 180.0f);
    }
}

int main(int argc, char const *argv[]) {
    sf::RenderWindow window( sf::VideoMode( 600, 600 ), "MOVEMENT" );

    sf::Texture lcu;
    lcu.loadFromFile("light_combat_unit.png");
    sf::Sprite body;
    body.setTexture(lcu);

    body.setPosition( 00.0f, 00.0f );
    CenterOrigin(&body);

    float max_speed = 200.0f;
    sf::Vector2f destination = sf::Vector2f(300.0f, 300.0f);

    double time_step = 1.0f / 60.0f;

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
                if ( event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ) {
                    sf::Vector2i pos = sf::Mouse::getPosition(window);
                    destination.x = static_cast<float>(pos.x);
                    destination.y = static_cast<float>(pos.y);
                }
            }
            UpdateSprite( &body, destination, time_since_last_update, max_speed );

            window.clear( sf::Color( 10, 100, 10 ) );
            window.draw( body );
            window.display();
            time_since_last_update = sf::seconds(0.0f);
        }
    }
    return 1;
}
