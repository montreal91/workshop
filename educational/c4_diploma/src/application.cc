
#include "application.h"

const int Application::MAX_VERTS = 400;
const sf::Time Application::TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);


Application::Application() :
_button(),
_current_graph_filename("graphs/default.txt"),
_font(),
_is_active(false),
_labels(),
_window(sf::VideoMode(1200, 610), "Diploma", sf::Style::Close),
_world()
{
  _window.setKeyRepeatEnabled(false);
  _font.loadFromFile("media/fonts/RobotoMono-Regular.ttf");

  auto gravity_type_lbl = _CreateEmptyLabel(sf::Color::Cyan);
  auto win_size = _window.getSize();
  gravity_type_lbl.setPosition(win_size.x / 2 + 2 * util::GAP, util::GAP);

  _labels["gravity_type"] = gravity_type_lbl;
  _button.SetAction(util::ActionType::Dummy);
  _button.SetText(_CreateEmptyLabel(sf::Color::Black));
  _button.SetString("Dummy button");
  _button.SetPosition(win_size.x / 2 + 2 * util::GAP, util::GAP + 20);

  _LoadData();
}

void Application::Run() {
  sf::Clock clock;
  sf::Time time_since_last_update = sf::Time::Zero;
  while (_window.isOpen()) {
    sf::Time dt = clock.restart();
    time_since_last_update += dt;

    while (time_since_last_update > TIME_PER_FRAME) {
      time_since_last_update -= TIME_PER_FRAME;
      _ProcessInput();
      _Update(TIME_PER_FRAME);
      _Render();
    }
  }
}

//
// Private methods
//

sf::Text Application::_CreateEmptyLabel(const sf::Color& text_color) const {
  auto label = sf::Text();
  label.setFont(_font);
  label.setString("");
  label.setColor(text_color);
  label.setCharacterSize(util::FONT_SIZE);
  return label;
}

void Application::_LoadData() {
  std::ifstream in(_current_graph_filename);
  auto gravity_type = 0;
  in >> gravity_type;
  _world.SetGravityType(static_cast<World::GravityType>(gravity_type));
  _SetGravityTypeLabel(static_cast<World::GravityType>(gravity_type));

  auto n=0;
  in >> n;
  if (n > MAX_VERTS) {
    throw std::length_error("Graph is too big.");
  }
  std::cout << "Number of vertices: " << n << "\n";
  std::cout << "Gravity type: " << gravity_type << "\n";
  std::unique_ptr<Graph> graph(new Graph(n));

  auto i=0, j=0;
  for (auto c=0; c<n*n; c++) {
    in >> i >> j;
    if (i < 0 || j < 0) {
      break;
    }
    graph->SetEdge(i, j, Graph::EdgeGravity::attraction);
  }
  _world.SetGraph(std::move(graph));
  _world.Init();
}

void Application::_OnActionDummy() {
  std::cout << "Dummy button is clicked\n";
}

void Application::_PrintTestData() const {
}

void Application::_ProcessInput() {
  sf::Event event;
  while (_window.pollEvent(event)) {
    if (event.type == sf::Event::KeyPressed) {
      _ProcessKeyPress(event.key);
    }
    if (event.type == sf::Event::MouseButtonPressed) {
      _ProcessMouseClick(event.mouseButton);
    }
    if (event.type == sf::Event::MouseButtonReleased) {
      _UnclickButtons();
    }
    if (event.type == sf::Event::Closed) {
      _window.close();
    }
    if (event.type == sf::Event::LostFocus) {
      _SetActive(false);
    }
  }
}

void Application::_ProcessKeyPress(const sf::Event::KeyEvent& key_event) {
  if (key_event.code == sf::Keyboard::B) {
    _world.ToggleBlackHoleOn();
  }
  if (key_event.code == sf::Keyboard::Q) {
    _window.close();
  }
  if (key_event.code == sf::Keyboard::P) {
    _PrintTestData();
  }
  if (key_event.code == sf::Keyboard::R) {
    _LoadData();
    _SetActive(false);
  }
  if (key_event.code == sf::Keyboard::Space) {
    _ToggleActive();
  }
}

void Application::_ProcessMouseClick(const sf::Event::MouseButtonEvent& event) {
  if (event.button == sf::Mouse::Button::Left) {
    // std::cout << "click" << event.x << " " << event.y << "\n";
    auto action = _button.HandleClick(event.x, event.y);
    if (action == util::ActionType::Dummy) {
      _OnActionDummy();
    }
  }
}

void Application::_Render() {
  _window.clear();
  _world.RenderVertexes(_window);
  _window.draw(_button);
  _RenderLabels();
  _window.display();
}

void Application::_RenderLabels() {
  for (auto lbl : _labels) {
    _window.draw(lbl.second);
  }
}

void Application::_SetActive(bool active) {
  _is_active = active;
}

void Application::_SetGravityTypeLabel(World::GravityType t) {
  auto label = _labels["gravity_type"];
  if (t == World::GravityType::constant) {
    label.setString("Gravity Type: Constant");
  }
  else if (t == World::GravityType::inv_linear) {
    label.setString("Gravity Type: Inv. Linear");
  }
  else if (t == World::GravityType::classic) {
    label.setString("Gravity Type: Classic");
  }
  else {
    throw std::invalid_argument("Wrong gravity type");
  }
  _labels["gravity_type"] = label;
}

void Application::_ToggleActive() {
  _is_active = !_is_active;
}

void Application::_UnclickButtons() {
  _button.Unclick();
}

void Application::_Update(const sf::Time& dt) {
  if (_is_active) {
    _world.Update(dt);
  }
}
