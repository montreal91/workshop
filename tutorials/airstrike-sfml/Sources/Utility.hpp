
#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

#include <sstream>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>


//TODO: replace it with a proper input
namespace sf {
class Sprite;
class Text;
} // namespace sf

class Animation;

std::string     toString( sf::Keyboard::Key key );

void            centerOrigin( sf::Sprite& sprite );
void            centerOrigin( sf::Text& text );
void            centerOrigin( Animation& animation );

float           toDegree( float radian );
float           toRadian( float degree );

int             randomInt( int exclusiveMax );

float           length( sf::Vector2f vector );
sf::Vector2f    unitVector( sf::Vector2f vector );


#endif // __UTILITY_HPP__
