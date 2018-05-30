
#pragma once

#include <iostream>
#include <vector>

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "utility.h"


class BoundingBox : public sf::Drawable {
public:
  explicit BoundingBox(b2World& world);
  explicit BoundingBox(b2World& world, b2Vec2 pos, float width, float height);

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual float GetHeight() const;
  virtual b2Vec2 GetPosition() const;
  virtual float GetWidth() const;
private:
  void _CreatePhysicalBody(b2World& world);
  void _InitCorners(const std::vector<b2Vec2>& corners);

  b2Body*         _body;
  sf::VertexArray _corners;
  float           _height;
  b2Vec2          _position;
  float           _width;
};
