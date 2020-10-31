
#include "app.h"

const std::string App::PY_CLASS_NAME = "Counter";
const std::string App::PY_MODULE_NAME = "lib";

App::App() {
  Py_SetProgramName(Py_DecodeLocale("App", NULL));
  Py_Initialize();
  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path.append(\".\")");

  PyObject* name = PyUnicode_DecodeFSDefault(PY_MODULE_NAME.data());
  PyObject* module = PyImport_Import(name);

  PyObject* consturctor = PyObject_GetAttrString(module, PY_CLASS_NAME.data());
  _counter = PyObject_CallObject(consturctor, NULL);
  std::cout << _GetString(_counter) << "\n";

  Py_XDECREF(consturctor);
  Py_XDECREF(module);
  Py_XDECREF(name);
}

App::~App() {
  Py_Finalize();
}

void App::Run() {
  PyObject* res;
  for (auto i=0; i<10; i++) {
    PyObject_CallMethod(_counter, "Inc", NULL);
    res = PyObject_CallMethod(_counter, "GetValue", NULL);
    std::cout << _GetString(res) << "\n"; 
  }
  PyObject_CallMethod(_counter, "Drop", NULL);
  res = PyObject_CallMethod(_counter, "GetValue", NULL);
  std::cout << _GetString(res) << "\n";
}

std::string App::_GetString(PyObject* obj) {
  PyObject* repr = PyObject_Repr(obj);
  PyObject* str = PyUnicode_AsEncodedString(repr, "utf-8", "~E~");
  const char* bytes = PyBytes_AS_STRING(str);

  Py_XDECREF(repr);
  Py_XDECREF(str);
  return std::string(bytes);
}
