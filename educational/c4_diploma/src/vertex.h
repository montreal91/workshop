#ifndef VERTEX_H
#define VERTEX_H

#include <cmath>
#include <iostream>

#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

class Vertex : public sf::Drawable {
public:
  explicit Vertex(b2World& world);
  explicit Vertex(b2World& world, float x, float y);

  virtual void AddForce(const b2Vec2& force);
  virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;
  virtual b2Vec2 GetPosition() const;
  virtual void SetPosition(const b2Vec2& pos);
  virtual void Update(const sf::Time& dt);

  const static float RADIUS;
  const static float SCALE;

private:
  virtual void CreatePhysicalBody(b2World& world, float x, float y);

  b2Body* body;
  sf::CircleShape dot;
};

float GetDistanceBetweenVertices(const Vertex& v1, const Vertex& v2);

#endif // VERTEX_H
