
#include <iostream>

#include "vector.h"

int main() {
  Vector2* vec = new Vector2(3.4, 5.6);
  std::cout << vec->x << " " << vec->y << "\n";
  return 0;
}
