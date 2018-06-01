
#pragma once

#include <algorithm>
#include <memory>

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "bounding_box.h"
#include "graph.h"
#include "utility.h"
#include "vertex.h"


class World {
public:
  //
  // Enumeration of all possible gravity types in this world
  //
  enum class GravityType : int {
    constant = 0,
    inv_linear = 1,
    classic = 2,
  };

  explicit World();

  bool AreMassesEqual() const;

  //
  // Sets initial world state.
  //
  void Init();

  //
  // Renders vertexes in provided window
  //
  void RenderVertexes(sf::RenderWindow& window) const;

  //
  // Sets graph that will be simulated.
  //
  void SetGraph(Graph::Ptr_t graph_ptr);

  //
  // Sets physical law of force of interaction between vertexes.
  //
  void SetGravityType(GravityType type);

  //
  // Turns on and off the black hole.
  //
  void ToggleBlackHoleOn();

  void ToggleEqualMasses();

  //
  // Main function for graph simulation.
  // Calculates and applies all forces and then does world step for a fraction
  // of time dt.
  //
  void Update(const sf::Time& dt);

private:
  typedef std::vector<Vertex*> UVertexIndex;

  static const float GRAVITATIONAL_CONSTANT;
  
  b2Vec2 _CalculateBlackHoleGravity(const Vertex& vertex) const;

  b2Vec2 _CalculateGravityBetweenVertexes(size_t i, size_t j) const;

  //
  // Returns normalized force direction applied to subject
  //
  b2Vec2 _CalculateGravityDirection(
    const Vertex& subject,
    const Vertex& object
  ) const;

  float _CalculateGravityMagnitude(
    const Vertex& subject,
    const Vertex& object
  ) const;

  sf::Color _CalculateVertexColor(size_t i) const;

  void _FillVertexIndex(UVertexIndex& index);

  void _InitVertexesObjects();

  void _InitVertexesPositions();


  float               _attraction;
  float               _black_hole_action_radius;
  bool                _black_hole_on;
  b2Vec2              _black_hole_position;
  bool                _equal_masses;
  GravityType         _gravity_type;
  b2World             _physical_world;
  BoundingBox         _bounding_box;
  float               _repulsion;
  std::vector<Vertex> _vertexes;
  Graph::Ptr_t        _graph;
};
