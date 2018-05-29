
#include "world.h"


World::World():
_physical_world(b2Vec2(0.0f, 0.0f)),
_vertexes()
{
  float black_hole_x = 1200;
  float black_hole_y = 600;
  _black_hole_position = b2Vec2(
    black_hole_x / 2 / Vertex::SCALE,
    black_hole_y / 2 / Vertex::SCALE
  );

  _black_hole_action_radius = _black_hole_position.y - 2;
  _gravity_type = GravityType::constant;
}

void World::Init() {
  // If there is no graph yet, or _graph pointer does not own any graph object,
  // there is nothing to do
  if (!_graph) {
    return;
  }
  _vertexes.clear();
  _InitVerticesObjects();
  _InitVerticesPositions();
}

void World::RenderVertexes(sf::RenderWindow& window) const {
  for (auto vertex : _vertexes) {
    window.draw(vertex);
  }
}

void World::SetGraph(Graph::Ptr_t graph_ptr) {
  _graph = std::move(graph_ptr);
}

void World::SetGravityType(World::GravityType type) {
  _gravity_type = type;
}

void World::Update(const sf::Time& dt) {
  for (int i=0; i<_vertexes.size(); i++) {
    for (int j=0; j<_vertexes.size(); j++) {
      b2Vec2 force = _CalculateForceDirection(_vertexes[i], _vertexes[j]);
      float magnitude = _CalculateForceMagnitude(
        _vertexes[i],
        _vertexes[j]
      );
      force *= magnitude;
      force *= -_graph->GetEdge(i, j);
      _vertexes[i].AddForce(force);
      _vertexes[i].AddForce(_CalculateBlackHoleForce(_vertexes[i]));
    }
  }
  _physical_world.Step(dt.asSeconds(), 8, 3);
  for (auto i = 0; i < _vertexes.size(); i++) {
    _vertexes[i].Update();
  }
}


//
// Private methods
//

b2Vec2 World::_CalculateBlackHoleForce(const Vertex& vertex) const {
  auto pos = vertex.GetPosition();
  auto direction = _black_hole_position - pos;

  auto distance = util::GetVectorNorm(direction);

  if (distance < _black_hole_action_radius) {
    return b2Vec2(0.0f, 0.0f);
  } else {
    direction = util::GetNormalizedVector(direction);
    auto magnitude = distance;
    return b2Vec2(direction.x * magnitude, direction.y * magnitude);
  }
}

b2Vec2 World::_CalculateForceDirection(
  const Vertex& subject,
  const Vertex& object
) const {
  b2Vec2 res = subject.GetPosition();
  res -= object.GetPosition();
  return util::GetNormalizedVector(res);
}

float World::_CalculateForceMagnitude(
  const Vertex& subject,
  const Vertex& object
) const {
  const auto distance = GetDistanceBetweenVertices(subject, object);
  if (_gravity_type == GravityType::constant) {
    return _GRAVITATIONAL_CONSTANT;
  }
  else if (_gravity_type == GravityType::inv_linear) {
    if (distance <= util::EPSILON) {
      return _GRAVITATIONAL_CONSTANT;
    } else {
      return _GRAVITATIONAL_CONSTANT / distance;
    }
  }
  else if (_gravity_type == GravityType::inv_quadratic) {
    if (distance <= util::EPSILON) {
      return _GRAVITATIONAL_CONSTANT;
    } else {
      return _GRAVITATIONAL_CONSTANT / distance / distance;
    }
  }
  else {
    throw std::invalid_argument("Gravity type should be 0, 1 or 2.");
  }
}

void World::_InitVerticesObjects() {
  for (auto i=0; i<_graph->GetSize(); i++) {
    Vertex v(_physical_world);
    _vertexes.push_back(v);
  }
}

void World::_InitVerticesPositions() {
  const auto PI = 3.141592f;
  auto phi = 2 * PI / _vertexes.size();
  auto r = _black_hole_action_radius * 0.25;

  for (auto i=0; i < _vertexes.size(); i++) {
    auto x = std::cos(phi * i) * r;
    auto y = std::sin(phi * i) * r;

    auto pos = b2Vec2(
      _black_hole_position.x + x,
      _black_hole_position.y + y
    );
    _vertexes[i].SetPosition(pos);
    _vertexes[i].Update();
  }
}
