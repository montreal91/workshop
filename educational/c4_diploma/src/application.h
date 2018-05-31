
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

#include "button.h"
#include "graph.h"
#include "utility.h"
#include "vertex.h"
#include "world.h"

//
// Main application class which manages vertex movement
// This class is not supposed to be subclassed.
//
class Application : private sf::NonCopyable {
public:
  explicit Application();

  void Run();

private:
  sf::Text _CreateEmptyLabel(const sf::Color& text_color) const;
  void _LoadData();

  //
  // Next methods are action handlers
  //

  void _OnActionDummy();

  void _PrintTestData() const;
  void _ProcessInput();
  void _ProcessKeyPress(const sf::Event::KeyEvent& key_event);
  void _ProcessMouseClick(const sf::Event::MouseButtonEvent& event);
  void _Render();
  void _RenderLabels();
  void _SetActive(bool active);
  void _SetGravityTypeLabel(World::GravityType t);
  void _ToggleActive();
  void _UnclickButtons();
  void _Update(const sf::Time& dt);

  static const std::string  FOLDER;
  static const int          MAX_VERTS;
  static const sf::Time     TIME_PER_FRAME;

  Button              _button;
  std::string         _current_graph_filename;
  sf::Font            _font;
  bool                _is_active;
  util::LabelHolder_t _labels;
  sf::RenderWindow    _window;
  World               _world;
};
