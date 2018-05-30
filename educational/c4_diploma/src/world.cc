
#include "world.h"


const float World::GRAVITATIONAL_CONSTANT = 1.75f;


World::World():
_attraction(GRAVITATIONAL_CONSTANT),
_black_hole_on(true),
_physical_world(b2Vec2(0.0f, 0.0f)),
_bounding_box(_physical_world, b2Vec2(), 20, 20),
_repulsion(GRAVITATIONAL_CONSTANT),
_vertexes()
{
  _black_hole_position = _bounding_box.GetPosition();
  _black_hole_position.x += _bounding_box.GetWidth() / 2.0;
  _black_hole_position.y += _bounding_box.GetHeight() / 2.0;

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

  _attraction = GRAVITATIONAL_CONSTANT;
  float density = _graph->GetDensity();
  _repulsion = GRAVITATIONAL_CONSTANT * density * _graph->GetSize();
}

void World::RenderVertexes(sf::RenderWindow& window) const {
  window.draw(_bounding_box);
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

void World::ToggleBlackHoleOn() {
  _black_hole_on = !_black_hole_on;
}

void World::Update(const sf::Time& dt) {
  for (int i=0; i<_vertexes.size(); i++) {
    for (int j=0; j<_vertexes.size(); j++) {
      _vertexes[i].AddForce(_CalculateGravityBetweenVertexes(i, j));
      _vertexes[i].AddForce(_CalculateBlackHoleGravity(_vertexes[i]));
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

b2Vec2 World::_CalculateBlackHoleGravity(const Vertex& vertex) const {
  if (!_black_hole_on) {
    return b2Vec2();
  }
  auto pos = vertex.GetPosition();
  auto direction = _black_hole_position - pos;

  auto distance = util::GetVectorNorm(direction);

  if (distance < _black_hole_action_radius) {
    return b2Vec2(0.0f, 0.0f);
  } else {
    direction = util::GetNormalizedVector(direction);
    return GRAVITATIONAL_CONSTANT * direction;
  }
}

b2Vec2 World::_CalculateGravityBetweenVertexes(size_t i, size_t j) const {
  auto subject = _vertexes[i];
  auto object = _vertexes[j];

  b2Vec2 force = _CalculateGravityDirection(subject, object);
  float magnitude = _CalculateGravityMagnitude(subject, object);
  force *= magnitude;

  auto edge = _graph->GetEdge(i, j);
  force *= -edge;

  if (edge == Graph::EdgeGravity::repulsion) {
    force *= _repulsion;
  }
  else if (edge == Graph::EdgeGravity::attraction) {
    force *= _attraction;
  }
  return force;
}

b2Vec2 World::_CalculateGravityDirection(
  const Vertex& subject,
  const Vertex& object
) const {
  b2Vec2 res = subject.GetPosition();
  res -= object.GetPosition();
  return util::GetNormalizedVector(res);
}

float World::_CalculateGravityMagnitude(
  const Vertex& subject,
  const Vertex& object
) const {
  
  const auto distance = GetDistanceBetweenVertices(subject, object);
  
  float mass_factor = subject.GetMass() * object.GetMass();

  if (_gravity_type == GravityType::constant) {
    return GRAVITATIONAL_CONSTANT * mass_factor;
  }
  else if (_gravity_type == GravityType::inv_linear) {
    if (distance <= util::EPSILON) {
      return GRAVITATIONAL_CONSTANT;
    } else {
      return GRAVITATIONAL_CONSTANT * mass_factor / distance;
    }
  }
  else if (_gravity_type == GravityType::inv_quadratic) {
    if (distance <= util::EPSILON) {
      return GRAVITATIONAL_CONSTANT;
    } else {
      return GRAVITATIONAL_CONSTANT * mass_factor / distance / distance;
    }
  }
  else {
    throw std::invalid_argument("Invalid gravity type.");
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

  // For now 11 is bounding box's size + 1
  auto index = 0;
  _vertexes[index].SetPosition(_black_hole_position);
  _vertexes[index].Update();

  for (auto i=1; i < 11 && index < _graph->GetSize(); i++) {
    auto step = 2.0f * PI / i / 10;
    for (auto j=0; j < i * 10; j++) {
      index++;
      if (index >= _graph->GetSize()) {
        break;
      }
      auto phi = step * j;
      auto x = std::cos(phi) * i;
      auto y = std::sin(phi) * i;

      auto pos = b2Vec2(
        _black_hole_position.x + x,
        _black_hole_position.y + y
      );
      _vertexes[index].SetPosition(pos);
      _vertexes[index].Update();
    }
  }
}
