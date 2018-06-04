
#pragma once

#include <cmath>
#include <map>
#include <string>

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

namespace util {

void CenterOrigin(sf::Text& text);
b2Vec2 GetNormalizedVector(const b2Vec2& vec);
float GetVectorNorm(const b2Vec2& vec);

const float EPSILON = 0.0001f;
const auto  FONT_SIZE = 15;
const auto  GAP = 5;
const auto  GRAVITY_STEP = 0.05;
const float RADIUS = 0.15f;
const float SCALE = 30.0f;
const sf::Vector2f SHIFT = sf::Vector2f(5.0, 5.0);


//
// Enumeration of all possible action types.
//
enum class ActionType : int {
  Dummy = -1,
  None = 0,
  SetGravityConst = 100,
  SetGravityInvLinear = 101,
  SetGravityClassic = 102,
  SetGravityLogarithmic = 103,
  SetGravityRadical = 104,
  SetGravityStep = 105,
  ToggleMasses = 10,
  UpdateGravityConstant = 200,
};

} // namespace util
