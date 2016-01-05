
#ifndef HELLO_WORLD_H_
#define HELLO_WORLD_H_

#include <iostream>

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class HelloWorld : public Gtk::Window {
public:
    HelloWorld();
    virtual ~HelloWorld();

protected:
    // Signal handlers:
    void on_button_clicked();

    // Member widgets:
    Gtk::Button m_button;
};

#endif
