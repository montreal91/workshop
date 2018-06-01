
#include "application.h"

const int Application::MAX_VERTS = 400;
const sf::Time Application::TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);


Application::Application() :
_buttons(),
_current_graph_filename("graphs/default.txt"),
_font(),
_is_active(false),
_labels(),
_window(sf::VideoMode(1200, 610), "Diploma", sf::Style::Close),
_world()
{
  _window.setKeyRepeatEnabled(false);
  _font.loadFromFile("media/fonts/RobotoMono-Regular.ttf");

  _InitButtons();
  _InitLabels();

  _world.SetGravityType(World::GravityType::classic);
  _SetGravityTypeLabel(World::GravityType::classic);
  _SetMassLabel(_world.AreMassesEqual());

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

void Application::_AdjustButtonsWidth() {
  auto max_width = 0.0;
  for (auto& button : _buttons) {
    if (button->GetSize().x > max_width) {
      max_width = button->GetSize().x;
    }
  }

  for (auto& button : _buttons) {
    button->SetWidth(max_width);
  }
}

Button::UPtr Application::_CreateButton(
  const std::string& title,
  util::ActionType action
) {
  Button::UPtr button(new Button());
  button->SetAction(action);
  button->SetText(_CreateEmptyLabel(sf::Color::Black));
  button->SetString(title);
  return button;
}

sf::Text Application::_CreateEmptyLabel(const sf::Color& text_color) const {
  auto label = sf::Text();
  label.setFont(_font);
  label.setString("");
  label.setColor(text_color);
  label.setCharacterSize(util::FONT_SIZE);
  return label;
}

void Application::_InitButtons() {
  const auto win_size = _window.getSize();
  const auto btns_x = win_size.x / 2 + 2 * util::GAP;
  const auto step = 20;
  const auto y_shift = 510;

  auto grv_btn1 = _CreateButton("Constant", util::ActionType::SetGravityConst);
  grv_btn1->SetPosition(btns_x, y_shift + util::GAP + step);

  auto grv_btn2 = _CreateButton(
    "Inv. Linear",
    util::ActionType::SetGravityInvLinear
  );
  grv_btn2->SetPosition(btns_x, y_shift + (util::GAP + step) * 2);

  auto grv_btn3 = _CreateButton("Classic", util::ActionType::SetGravityClassic);
  grv_btn3->SetPosition(btns_x, y_shift + (util::GAP + step) * 3);

  auto mass_btn = _CreateButton("Toggle Masses", util::ActionType::ToggleMasses);
  mass_btn->SetPosition(btns_x, y_shift - (util::GAP + step));

  _buttons.push_back(std::move(grv_btn1));
  _buttons.push_back(std::move(grv_btn2));
  _buttons.push_back(std::move(grv_btn3));
  _buttons.push_back(std::move(mass_btn));

  _AdjustButtonsWidth();
}

void Application::_InitLabels() {
  const auto win_size = _window.getSize();
  const auto lbls_x = win_size.x / 2 + 2 * util::GAP;
  const auto step = 10;

  auto gravity_type_lbl = _CreateEmptyLabel(sf::Color::Cyan);
  gravity_type_lbl.setPosition(lbls_x, util::GAP);

  auto mass_lbl = _CreateEmptyLabel(sf::Color::Cyan);
  mass_lbl.setPosition(lbls_x, (util::GAP + step) * 2);

  _labels["gravity_type"] = gravity_type_lbl;
  _labels["mass"] = mass_lbl;
}

void Application::_LoadData() {
  std::ifstream in(_current_graph_filename);

  auto n=0;
  in >> n;
  if (n > MAX_VERTS) {
    throw std::length_error("Graph is too big.");
  }
  std::unique_ptr<Graph> graph(new Graph(n));

  auto i=0, j=0, e=0;
  for (auto c=0; c<n*n; c++) {
    in >> i >> j;
    if (i < 0 || j < 0) {
      break;
    }
    graph->SetEdge(i, j, Graph::EdgeGravity::attraction);
    e++;
  }
  std::cout << "Number of vertices: " << n << "\n";
  std::cout << "Number of edges:    " << e << "\n";
  std::cout << "Graph density:      " << graph->GetDensity() << "\n";
  _world.SetGraph(std::move(graph));
  _world.Init();
}

void Application::_OnActionDummy() {
  std::cout << "Dummy button is clicked\n";
}

void Application::_OnActionSetGravityClassic() {
  _UpdateGravity(World::GravityType::classic);
}

void Application::_OnActionSetGravityConst() {
  _UpdateGravity(World::GravityType::constant);
}

void Application::_OnActionSetGravityInvLinear() {
  _UpdateGravity(World::GravityType::inv_linear);
}

void Application::_OnActionToggleMasses() {
  _SetActive(false);
  _world.ToggleEqualMasses();
  _world.Init();
  _SetMassLabel(_world.AreMassesEqual());
}

void Application::_PrintTestData() const {
}

bool Application::_ProcessAction(util::ActionType action) {
  if (action == util::ActionType::Dummy) {
    _OnActionDummy();
    return true;
  }
  else if (action == util::ActionType::SetGravityConst) {
    _OnActionSetGravityConst();
    return true;
  }
  else if (action == util::ActionType::SetGravityInvLinear) {
    _OnActionSetGravityInvLinear();
    return true;
  }
  else if (action == util::ActionType::SetGravityClassic) {
    _OnActionSetGravityClassic();
    return true;
  }
  else if (action == util::ActionType::ToggleMasses) {
    _OnActionToggleMasses();
  }
  else if (action == util::ActionType::None) {
    return false;
  }
  else {
    throw std::logic_error("Incorrect action.");
  }
  return false; // This line makes compiler happy;
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
    _world.Init();
    _SetActive(false);
  }
  if (key_event.code == sf::Keyboard::Space) {
    _ToggleActive();
  }
}

void Application::_ProcessMouseClick(const sf::Event::MouseButtonEvent& event) {
  if (event.button != sf::Mouse::Button::Left) {
    return;
  }
  for (auto& button : _buttons) {
    if (_ProcessAction(button->HandleClick(event.x, event.y))) {
      break;
    }
  }
}

void Application::_Render() {
  _window.clear();
  _world.RenderVertexes(_window);
  _RenderButtons();
  _RenderLabels();
  _window.display();
}

void Application::_RenderButtons() {
  for (auto& button : _buttons) {
    button->draw(_window, sf::RenderStates::Default);
  }
}

void Application::_RenderLabels() {
  for (auto& lbl : _labels) {
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

void Application::_SetMassLabel(bool mass) {
  if (!mass) {
    _labels["mass"].setString("Degree-based masses: ON");
  } else {
    _labels["mass"].setString("Degree-based masses: OFF");
  }
}

void Application::_ToggleActive() {
  _is_active = !_is_active;
}

void Application::_UnclickButtons() {
  for (auto& button : _buttons) {
    button->Unclick();
  }
}

void Application::_Update(const sf::Time& dt) {
  if (_is_active) {
    _world.Update(dt);
  }
}

void Application::_UpdateGravity(World::GravityType t) {
  _world.SetGravityType(t);
  _SetGravityTypeLabel(t);
}
