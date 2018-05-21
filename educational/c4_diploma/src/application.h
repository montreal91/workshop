
#ifndef APPLICATION_H
#define APPLICATION_H

#include <cmath>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <thread>
#include <vector>


#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "vertex.h"

// Main application class which manages vertex movement
// This class is not supposed to be subclassed.
class Application : private sf::NonCopyable {
public:
  static const float EPSILON;

  enum GravityType : int {
    constant = 0,
    inv_linear = 1,
    inv_quadratic = 2,
  };

  Application();

  void Run();
private:
  // static const int GRV_CONSTANT;
  // static const int GRV_INV_LINEAR;
  // static const int GRV_INV_QUADRATIC;
  b2Vec2 CalculateBlackHoleForce(const Vertex& vertex) const;

  // Returns normalized force direction applied to subject
  b2Vec2 CalculateForceDirection(const Vertex& subject, const Vertex& object) const;
  float CalculateForceMagnitude(
    const Vertex& subjet,
    const Vertex& object
  ) const;

  void InitVerticesPositions();
  void LoadData(std::istream& in);
  void PrintTestData() const;
  void ProcessInput();
  void Render();
  void Update(const sf::Time& dt);

  typedef std::vector<std::vector<float>> Matrix_t;

  static const sf::Time TIME_PER_FRAME;

  // This value should be constant too,
  // But it is loaded during runtime rather than compile-time,
  // so it can't be const.
  float GRAVITATIONAL_CONSTANT;

  Matrix_t adjacency_matrix;
  float black_hole_action_radius;
  b2Vec2 black_hole_position;
  int gravity_type;
  b2World physical_world;
  std::vector<Vertex> vertices;
  sf::RenderWindow window;
};

//TODO: put utility functions into separate file
namespace util {
b2Vec2 GetNormalizedVector(const b2Vec2& vec);
float GetVectorNorm(const b2Vec2& vec);
} // namespace util

#endif // APPLICATION_H
