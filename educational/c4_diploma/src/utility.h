
#pragma once

#include <cmath>

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

namespace util {

b2Vec2 GetNormalizedVector(const b2Vec2& vec);
float GetVectorNorm(const b2Vec2& vec);

const float EPSILON = 0.0001f;
const float RADIUS = 0.1f;
const float SCALE = 30.0f;
const sf::Vector2f SHIFT = sf::Vector2f(5.0, 5.0);

} // namespace util
