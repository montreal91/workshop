
#pragma once


#include <cassert>
#include <cmath>
#include <ctime>
#include <sstream>
#include <string>
#include <random>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Animation.hpp"


std::string     toString( sf::Keyboard::Key key );

void            centerOrigin( sf::Sprite& sprite );
void            centerOrigin( sf::Text& text );
void            centerOrigin( Animation& animation );

float           toDegree( float radian );
float           toRadian( float degree );

int             randomInt( int exclusiveMax );

float           length( sf::Vector2f vector );
sf::Vector2f    unitVector( sf::Vector2f vector );
