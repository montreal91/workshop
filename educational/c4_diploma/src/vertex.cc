
#include "vertex.h"


Vertex::Vertex(b2World& world) :
_dot(util::RADIUS * util::SCALE)
{
  _dot.setFillColor(sf::Color::Cyan);
  _CreatePhysicalBody(world, 0.0f, 0.0f, 1.0f);
}

Vertex::Vertex(b2World& world, float x, float y) :
_dot(util::RADIUS * util::SCALE)
{
  _dot.setFillColor(sf::Color::Cyan);
  _CreatePhysicalBody(world, x, y, 1.0f);
}

Vertex::Vertex(b2World& world, float x, float y, float mass) :
_dot(util::RADIUS * util::SCALE)
{
  _dot.setFillColor(sf::Color::Cyan);
  _CreatePhysicalBody(world, x, y, mass);
}

void Vertex::AddForce(const b2Vec2& force) {
  _body->ApplyForceToCenter(force, true);
}

float Vertex::GetMass() const {
  return static_cast<float>(_body->GetMass());
}

b2Vec2 Vertex::GetPosition() const {
  return _body->GetPosition();
}

void Vertex::SetColor(const sf::Color& color) {
  _dot.setFillColor(color);
}

void Vertex::SetMass(int mass) {
  b2MassData mass_data;
  mass_data.center = b2Vec2();
  mass_data.mass = mass;
  _body->SetMassData(&mass_data);
}

void Vertex::SetPosition(const b2Vec2& pos) {
  _body->SetTransform(pos, 0);
}

void Vertex::Update() {
  b2Vec2 pos = _body->GetPosition();
  _dot.setPosition(util::SCALE * pos.x, util::SCALE * pos.y);
}

//
// Private methods
//

void Vertex::draw(sf::RenderTarget& target, sf::RenderStates states) const{
  target.draw(_dot, states);
}

void Vertex::_CreatePhysicalBody(b2World& world, float x, float y, float mass) {
  b2BodyDef body_def;
  body_def.position = b2Vec2(x, y);
  body_def.type = b2_dynamicBody;

  b2CircleShape circle_shape;
  circle_shape.m_p.Set(0, 0);
  circle_shape.m_radius = util::RADIUS;

  b2FixtureDef fixture_def;
  fixture_def.density  = 2.0f;
  fixture_def.friction = 0.0f;
  fixture_def.shape = &circle_shape;

  _body = world.CreateBody(&body_def);
  _body->CreateFixture(&fixture_def);

  b2MassData mass_data;
  mass_data.center = b2Vec2();
  mass_data.mass = mass;
  _body->SetMassData(&mass_data);
}

float GetDistanceBetweenVertexes(const Vertex& v1, const Vertex& v2) {
  b2Vec2 pos1 = v1.GetPosition();
  b2Vec2 pos2 = v2.GetPosition();
  
  b2Vec2 diff = pos2 - pos1;
  return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}
