
#include "application.h"

const std::string Application::FOLDER = "data/";
const std::string Application::GRAVITY_CONSTANT_STR = "Gravity Constant: ";
const int         Application::MAX_VERTS = 400;
const sf::Time    Application::TIME_PER_FRAME = sf::seconds(1.0f / 30.0f);


Application::Application() :
_buttons(),
_current_graph_filename("data/default.txt"),
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

  _world.SetGravityType(World::GravityType::Classic);
  _SetGravityTypeLabel(World::GravityType::Classic);
  _SetMassLabel(_world.AreMassesEqual());

  _LoadData();
  _LoadFiles();
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

void Application::_InitButtons() {
  const auto win_size = _window.getSize();
  const auto btns_x = win_size.x / 2 + 2 * util::GAP;
  const auto step = 20;
  const auto y_shift = 435;

  auto grv_btn1 = Button::CreateButton(
      "Constant",
      _font,
      util::ActionType::SetGravityConst
  );
  grv_btn1->SetPosition(btns_x, y_shift + util::GAP + step);

  auto grv_btn2 = Button::CreateButton(
      "Inv. Linear",
      _font,
      util::ActionType::SetGravityInvLinear
  );
  grv_btn2->SetPosition(btns_x, y_shift + (util::GAP + step) * 2);

  auto grv_btn3 = Button::CreateButton(
      "Classic",
      _font,
      util::ActionType::SetGravityClassic
  );
  grv_btn3->SetPosition(btns_x, y_shift + (util::GAP + step) * 3);

  auto grv_btn4 = Button::CreateButton(
    "Logarithmic",
    _font,
    util::ActionType::SetGravityLogarithmic
  );
  grv_btn4->SetPosition(btns_x, y_shift + (util::GAP + step) * 4);

  auto grv_btn5 = Button::CreateButton(
    "Radical",
    _font,
    util::ActionType::SetGravityRadical
  );
  grv_btn5->SetPosition(btns_x, y_shift + (util::GAP + step) * 5);

  auto grv_btn6 = Button::CreateButton(
    "Step",
    _font,
    util::ActionType::SetGravityStep
  );
  grv_btn6->SetPosition(btns_x, y_shift + (util::GAP + step) * 6);

  auto mass_btn = Button::CreateButton(
    "Toggle Masses",
    _font,
    util::ActionType::ToggleMasses
  );
  mass_btn->SetPosition(btns_x, y_shift - (util::GAP + step));

  _buttons.push_back(std::move(grv_btn1));
  _buttons.push_back(std::move(grv_btn2));
  _buttons.push_back(std::move(grv_btn3));
  _buttons.push_back(std::move(grv_btn4));
  _buttons.push_back(std::move(grv_btn5));
  _buttons.push_back(std::move(grv_btn6));
  _buttons.push_back(std::move(mass_btn));

  _AdjustButtonsWidth();
}

void Application::_InitLabels() {
  const auto win_size = _window.getSize();
  const auto lbls_x = win_size.x / 2 + 2 * util::GAP;
  const auto step = 15;
  const auto y_shift = -10;

  auto density_label = util::CreateEmptyLabel(sf::Color::Cyan, _font);
  density_label.setPosition(lbls_x, y_shift + util::GAP + step);

  auto gravity_constant_lbl = util::CreateEmptyLabel(sf::Color::Cyan, _font);
  gravity_constant_lbl.setPosition(lbls_x, y_shift + (util::GAP + step) * 2);

  auto gravity_type_lbl = util::CreateEmptyLabel(sf::Color::Cyan, _font);
  gravity_type_lbl.setPosition(lbls_x, y_shift + (util::GAP + step) * 3);

  auto mass_lbl = util::CreateEmptyLabel(sf::Color::Cyan, _font);
  mass_lbl.setPosition(lbls_x, y_shift + (util::GAP + step) * 4);

  _labels["density"] = density_label;
  _labels["gravity_constant"] = gravity_constant_lbl;
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
  _labels["density"].setString(
      "Graph Density: " + std::to_string(graph->GetDensity())
  );
  _labels["gravity_constant"].setString(
    GRAVITY_CONSTANT_STR + std::to_string(_world.GetGravityConstant())
  );
  _world.SetGraph(std::move(graph));
  _world.Init();
}

void Application::_LoadFiles() {
  Poco::File graph_dir("data");
  std::vector<std::string> files;
  graph_dir.list(files);

  FileList::UPtr ptr(new FileList(files, _font));
  _file_list = std::move(ptr);

  _file_list->setPosition(750, 410);
  _file_list->SetWidth(_buttons[0]->GetSize().x);
}

void Application::_OnActionDummy() {
  std::cout << "Dummy button is clicked\n";
}

void Application::_OnActionReloadFile() {
  std::cout << _file_list->GetValue() << "\n";
  _SetActive(false);
  _current_graph_filename = FOLDER + _file_list->GetValue();
  _LoadData();
}

void Application::_OnActionSetGravityClassic() {
  _UpdateGravity(World::GravityType::Classic);
}

void Application::_OnActionSetGravityConst() {
  _UpdateGravity(World::GravityType::Constant);
}

void Application::_OnActionSetGravityInvLinear() {
  _UpdateGravity(World::GravityType::InvLinear);
}

void Application::_OnActionSetGravityLogarithmic() {
  _UpdateGravity(World::GravityType::Logarithmic);
}

void Application::_OnActionSetGravityStep() {
  _UpdateGravity(World::GravityType::Step);
}

void Application::_OnActionSetGravityRadical() {
  _UpdateGravity(World::GravityType::Radical);
}

void Application::_OnActionToggleMasses() {
  _SetActive(false);
  _world.ToggleEqualMasses();
  _world.Init();
  _SetMassLabel(_world.AreMassesEqual());
}

void Application::_PrintTestData() const {}

bool Application::_ProcessAction(util::ActionType action) {
  if (action == util::ActionType::Dummy) {
    _OnActionDummy();
    return true;
  }
  else if (action == util::ActionType::ReloadFile) {
    _OnActionReloadFile();
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
  else if (action == util::ActionType::SetGravityLogarithmic) {
    _OnActionSetGravityLogarithmic();
    return true;
  }
  else if (action == util::ActionType::SetGravityRadical) {
    _OnActionSetGravityRadical();
    return true;
  }
  else if (action == util::ActionType::SetGravityStep) {
    _OnActionSetGravityStep();
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
  if (key_event.code == sf::Keyboard::Down) {
    _world.DecreaseGravity(util::GRAVITY_STEP);
    _labels["gravity_constant"].setString(
        GRAVITY_CONSTANT_STR + std::to_string(_world.GetGravityConstant())
    );
  }
  if (key_event.code == sf::Keyboard::Up) {
    _world.IncreaseGravity(util::GRAVITY_STEP);
    _labels["gravity_constant"].setString(
        GRAVITY_CONSTANT_STR + std::to_string(_world.GetGravityConstant())
    );
  }
  if (key_event.code == sf::Keyboard::Space) {
    _ToggleActive();
  }
}

void Application::_ProcessMouseClick(const sf::Event::MouseButtonEvent& event) {
  if (event.button != sf::Mouse::Button::Left) {
    return;
  }
  if (_ProcessAction(_file_list->HandleClick(event.x, event.y))) {
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
  _file_list->draw(_window, sf::RenderStates::Default);
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
  const auto gtype = std::string("Gravity Type: ");
  auto label = _labels["gravity_type"];
  if (t == World::GravityType::Constant) {
    label.setString(gtype + "Constant");
  }
  else if (t == World::GravityType::InvLinear) {
    label.setString(gtype + "Inv. Linear");
  }
  else if (t == World::GravityType::Classic) {
    label.setString(gtype + "Classic");
  }
  else if (t == World::GravityType::Logarithmic) {
    label.setString(gtype + "Logarithmic");
  }
  else if (t == World::GravityType::Radical) {
    label.setString(gtype + "Radical");
  }
  else if (t == World::GravityType::Step) {
    label.setString(gtype + "Step");
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
  _file_list->Unclick();
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
