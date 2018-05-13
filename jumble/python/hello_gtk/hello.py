
import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

try:
    gi.require_foreign("cairo")
except ImportError:
    print("No pycairo integration :(")

window = Gtk.Window(title="Hello World")
window.show()
window.connect("destroy", Gtk.main_quit)
Gtk.main()
