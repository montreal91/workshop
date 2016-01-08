
#ifndef GTKMM_EXAMPLEWINDOW_H_
#define GTKMM_EXAMPLEWINDOW_H_

#include <iostream>

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window {
public:
    ExampleWindow();
    virtual ~ExampleWindow();

protected:
    // Signal handlers:
    void on_button_quit();

    // Tree model columns:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumns() {
            add(m_col_id);
            add(m_col_name);
            add(m_col_number);
            add(m_col_percentage);
        }
        Gtk::TreeModelColumn<unsigned int> m_col_id;
        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
        Gtk::TreeModelColumn<short> m_col_number;
        Gtk::TreeModelColumn<int> m_col_percentage;
    };
    ModelColumns m_Columns;

    // Child widgets:
    Gtk::Box m_VBox;

    Gtk::ScrolledWindow m_ScrolledWindow;
    Gtk::TreeView m_TreeView;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

    Gtk::ButtonBox m_ButtonBox;
    Gtk::Button m_Button_Quit;
};

#endif // GTKMM_EXAMPLEWINDOW_H_
