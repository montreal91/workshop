
#pragma once

#include <cmath>

#include <Box2D/Box2D.h>

namespace util {

b2Vec2 GetNormalizedVector(const b2Vec2& vec);
float GetVectorNorm(const b2Vec2& vec);

const float EPSILON = 0.0001;

} // namespace util
