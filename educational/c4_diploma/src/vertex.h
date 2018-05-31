
#pragma once

#include <cmath>
#include <iostream>

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include "utility.h"

//
// Class for physical vertexes that live in physical world and can be drawn in
// sf::RenderTarget
//
class Vertex : public sf::Drawable {
public:
  explicit Vertex(b2World& world);
  explicit Vertex(b2World& world, float x, float y);
  explicit Vertex(b2World& world, float x, float y, float mass);

  //
  // Adds Force to the vertex.
  // Force is measured in newtons.
  //
  virtual void AddForce(const b2Vec2& force);


  //
  // Returns vertex' mass measured in kilograms.
  //
  virtual float GetMass() const;

  //
  // Returns vertex' position in the physical world.
  //
  virtual b2Vec2 GetPosition() const;

  //
  // Sets vertex' color that appears on the screen
  //
  virtual void SetColor(const sf::Color& color);

  //
  // Sets vertex' position in the physical world measured in meters.
  //
  virtual void SetPosition(const b2Vec2& pos);

  //
  // Updates vertex' representation.
  //
  virtual void Update();

private:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  virtual void _CreatePhysicalBody(b2World& world, float x, float y, float mass);

  b2Body*         _body;
  sf::CircleShape _dot;
};

float GetDistanceBetweenVertices(const Vertex& v1, const Vertex& v2);
