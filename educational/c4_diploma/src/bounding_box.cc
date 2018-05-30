
#include "bounding_box.h"

BoundingBox::BoundingBox(b2World& world) :
_corners(sf::LinesStrip, 4+1),
_height(1),
_position(b2Vec2()),
_width(1)
{
  _CreatePhysicalBody(world);
}

BoundingBox::BoundingBox(b2World& world, b2Vec2 pos, float width, float height):
_corners(sf::LinesStrip, 4+1),
_height(height),
_position(pos),
_width(width)
{
  _CreatePhysicalBody(world);
}

void BoundingBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(_corners, states);
}

float BoundingBox::GetHeight() const {
  return _height; 
}

b2Vec2 BoundingBox::GetPosition() const {
  return _position;
}

float BoundingBox::GetWidth() const {
  return _width;
}

void BoundingBox::_CreatePhysicalBody(b2World& world) {
  b2BodyDef body_def;
  body_def.position = b2Vec2(_position);
  body_def.type = b2_staticBody;

  std::vector<b2Vec2> corners;
  corners.push_back(b2Vec2(_position));
  corners.push_back(b2Vec2(_position.x + _width, _position.y));
  corners.push_back(b2Vec2(_position.x + _width, _position.y + _height));
  corners.push_back(b2Vec2(_position.x, _position.y + _height));

  _InitCorners(corners);

  b2ChainShape box;
  box.CreateLoop(&corners.front(), corners.size());

  b2FixtureDef fixture_def;
  fixture_def.density  = 2.0f;
  fixture_def.friction = 0.7f;
  fixture_def.shape = &box;

  _body = world.CreateBody(&body_def);
  _body->CreateFixture(&fixture_def);
}

void BoundingBox::_InitCorners(const std::vector<b2Vec2>& corners) {
  sf::Vector2f screen_pos = sf::Vector2f(0.0, 0.0);
  for (auto i=0; i<corners.size(); i++) {
    screen_pos.x = corners[i].x * util::SCALE;
    screen_pos.y = corners[i].y * util::SCALE;
    screen_pos += util::SHIFT;
    _corners[i] = sf::Vertex(screen_pos, sf::Color::Cyan);
  }
  screen_pos.x = corners[0].x * util::SCALE;
  screen_pos.y = corners[0].y * util::SCALE;
  screen_pos += util::SHIFT;
  _corners[4] = sf::Vertex(screen_pos, sf::Color::Cyan);
}
