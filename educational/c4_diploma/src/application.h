
#pragma once

#include <cstring>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>


#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "graph.h"
#include "utility.h"
#include "vertex.h"
#include "world.h"

// Main application class which manages vertex movement
// This class is not supposed to be subclassed.
class Application : private sf::NonCopyable {
public:
  explicit Application();

  void Run();

private:
  void _LoadData(std::istream& in);
  void _PrintTestData() const;
  void _ProcessInput();
  void _Render();
  void _Update(const sf::Time& dt);

  static const std::string FOLDER;
  static const sf::Time TIME_PER_FRAME;

  sf::RenderWindow _window;
  World _world;
};
