
#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
// #include <vector>

class Vector2 {
public:
  Vector2();
  Vector2(double x, double y);
  Vector2(const Vector2& v);

  virtual double GetNorm() const;
  virtual Vector2 GetNormalized() const;

  double x;
  double y;
};

Vector2 operator+(const Vector2& vec1, const Vector2& vec2);
Vector2 operator-(const Vector2& vec1, const Vector2& vec2);

#endif // VECTOR_H
