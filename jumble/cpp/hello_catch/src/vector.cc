
#include "vector.h"

Vector2::Vector2() {
  this->x = 0.0;
  this->y = 0.0;
}

Vector2::Vector2(double x, double y) {
  this->x = x;
  this->y = y;
}

Vector2::Vector2(const Vector2& vec) {
  this->x = vec.x;
  this->y = vec.y;
}

double Vector2::GetNorm() const {
  return std::sqrt(x * x + y * y);
}

Vector2 Vector2::GetNormalized() const {
  auto norm = this->GetNorm();
  return Vector2(x / norm, y / norm);
}

Vector2 operator+(const Vector2& vec1, const Vector2& vec2) {
  return Vector2(vec1.x + vec2.x, vec1.y + vec2.y);
}

Vector2 operator-(const Vector2& vec1, const Vector2& vec2) {
  return Vector2(vec1.x - vec2.x, vec1.y - vec2.y);
}
