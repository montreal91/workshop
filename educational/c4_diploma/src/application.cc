
#include "application.h"


const sf::Time Application::TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);


Application::Application() :
_current_graph_filename("graphs/default.txt"),
_is_active(false),
_window(sf::VideoMode(1200, 600), "Diploma", sf::Style::Close),
_world()
{
  _window.setKeyRepeatEnabled(false);

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

void Application::_LoadData() {
  std::ifstream in(_current_graph_filename);
  auto gravity_type = 0;
  in >> gravity_type;
  _world.SetGravityType(static_cast<World::GravityType>(gravity_type));

  auto n=0;
  in >> n;
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

void Application::_PrintTestData() const {}

void Application::_ProcessInput() {
  sf::Event event;
  while (_window.pollEvent(event)) {
    if (event.type == sf::Event::KeyPressed) {
      _ProcessKeyPress(event.key);
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

void Application::_Render() {
  _window.clear();
  _world.RenderVertexes(_window);
  _window.display();
}

void Application::_SetActive(bool active) {
  _is_active = active;
}

void Application::_ToggleActive() {
  _is_active = !_is_active;
}

void Application::_Update(const sf::Time& dt) {
  if (_is_active) {
    _world.Update(dt);
  }
}
