
#include <gtkmm/application.h>

#include "helloworld.h"

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

    HelloWorld hw;

    return app->run(hw);
}
