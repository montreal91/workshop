
#include "vertex.h"

const float Vertex::RADIUS = 0.25f;
const float Vertex::SCALE = 30.0f;

Vertex::Vertex(b2World& world) :
dot(RADIUS * SCALE)
{
  this->dot.setFillColor(sf::Color::Magenta);
  this->dot.setPosition(sf::Vector2f(550, 300));

  this->CreatePhysicalBody(world, 0.0f, 0.0f);
}

Vertex::Vertex(b2World& world, float x, float y) :
  dot(RADIUS * SCALE)
{
  this->dot.setFillColor(sf::Color::Magenta);
  this->dot.setPosition(sf::Vector2f(x, y));

  this->CreatePhysicalBody(world, x, y);
}

void Vertex::AddForce(const b2Vec2& force) {
  this->body->ApplyForceToCenter(force, true);
}

void Vertex::draw(sf::RenderTarget& target, sf::RenderStates states) const{
  target.draw(this->dot, states);
}

b2Vec2 Vertex::GetPosition() const {
  return this->body->GetPosition();
}

void Vertex::Update(const sf::Time& dt) {
  b2Vec2 pos = this->body->GetPosition();
  this->dot.setPosition(SCALE * pos.x, SCALE * pos.y);
}

void Vertex::CreatePhysicalBody(b2World& world, float x, float y) {
  b2BodyDef body_def;
  body_def.position = b2Vec2(x, y);
  body_def.type = b2_dynamicBody;

  b2CircleShape circle_shape;
  circle_shape.m_p.Set(0, 0);
  circle_shape.m_radius = RADIUS;

  b2FixtureDef fixture_def;
  fixture_def.density  = 1.0f;
  fixture_def.friction = 0.7f;
  fixture_def.shape = &circle_shape;

  this->body = world.CreateBody(&body_def);
  this->body->CreateFixture(&fixture_def);

  std::cout << "Mass: " << this->body->GetMass() << "\n";
}

float GetDistanceBetweenVertices(const Vertex& v1, const Vertex& v2) {
  b2Vec2 pos1 = v1.GetPosition();
  b2Vec2 pos2 = v2.GetPosition();
  
  b2Vec2 diff = pos2 - pos1;
  return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}
