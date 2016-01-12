
#include <gtkmm/application.h>

#include "examplewindow.h"

int
main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    ExampleWindow window;

    return app->run(window);
}
