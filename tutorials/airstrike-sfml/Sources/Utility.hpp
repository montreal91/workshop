
#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

#include <sstream>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>


namespace sf {
    class Sprite;
    class Text;
} // namespace sf

std::string     toString( sf::Keyboard::Key key );

void            centerOrigin( sf::Sprite& sprite );
void            centerOrigin( sf::Text& text );

float           toDegree( float radian );
float           toRadian( float degree );

int             randomInt( int exclusiveMax );

float           length( sf::Vector2f vector );
sf::Vector2f    unitVector( sf::Vector2f vector );


#endif // __UTILITY_HPP__
