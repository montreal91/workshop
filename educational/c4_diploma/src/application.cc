
#include "application.h"


const sf::Time Application::TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);

Application::Application() :
_window(sf::VideoMode(1200, 600), "Diploma", sf::Style::Close),
_world()
{
  _window.setKeyRepeatEnabled(false);

  std::ifstream fileinput("graph.txt");
  _LoadData(fileinput);
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


void Application::_LoadData(std::istream& in) {
  int n;
  in >> n;
  std::cout << "Number of vertices: " << n << "\n";

  auto gravity_type = 0;
  in >> gravity_type;
  _world.SetGravityType(static_cast<World::GravityType>(gravity_type));

  std::unique_ptr<Graph> graph(new Graph(n));
  float tmp = 0;
  for (auto i=0; i<n; i++) {
    for (auto j=0; j<n; j++) {
      in >> tmp;
      graph->SetEdge(i, j, tmp);
    }
  }
  _world.SetGraph(std::move(graph));
  _world.Init();
}

void Application::_PrintTestData() const {}

void Application::_ProcessInput() {
  sf::Event event;
  while (_window.pollEvent(event)) {
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Q) {
        _window.close();
      }
      if (event.key.code == sf::Keyboard::P) {
        _PrintTestData();
      }
    }
    if (event.type == sf::Event::Closed) {
      _window.close();
    }
  }
}

void Application::_Render() {
  _window.clear();
  _world.RenderVertexes(_window);
  _window.display();
}

void Application::_Update(const sf::Time& dt) {
  _world.Update(dt);
}
