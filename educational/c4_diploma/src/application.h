
#pragma once

#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
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
  typedef std::vector<Button::UPtr> ButtonHolder;
  typedef std::map<std::string, sf::Text> LabelHolder;

  void _AdjustButtonsWidth();
  Button::UPtr _CreateButton(const std::string& title, util::ActionType action);
  sf::Text _CreateEmptyLabel(const sf::Color& text_color) const;
  void _InitButtons();
  void _InitLabels();
  void _LoadData();

  void _OnActionDummy();
  void _OnActionSetGravityClassic();
  void _OnActionSetGravityConst();
  void _OnActionSetGravityInvLinear();
  void _OnActionToggleMasses();

  void _PrintTestData() const;
  bool _ProcessAction(util::ActionType action);
  void _ProcessInput();
  void _ProcessKeyPress(const sf::Event::KeyEvent& key_event);
  void _ProcessMouseClick(const sf::Event::MouseButtonEvent& event);
  void _Render();
  void _RenderButtons();
  void _RenderLabels();
  void _SetActive(bool active);
  void _SetGravityTypeLabel(World::GravityType t);
  void _SetMassLabel(bool mass);
  void _ToggleActive();
  void _UnclickButtons();
  void _Update(const sf::Time& dt);
  void _UpdateGravity(World::GravityType t);

  static const std::string  FOLDER;
  static const int          MAX_VERTS;
  static const sf::Time     TIME_PER_FRAME;

  ButtonHolder      _buttons;
  std::string       _current_graph_filename;
  sf::Font          _font;
  bool              _is_active;
  LabelHolder       _labels;
  sf::RenderWindow  _window;
  World             _world;
};
