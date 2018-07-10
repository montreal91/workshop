
#pragma once

#include <iostream>
#include <string>

#include <Python.h>


class App {
public:
  App();
  ~App();

  void Run();

private:
  static const std::string PY_CLASS_NAME;
  static const std::string PY_MODULE_NAME;

  static std::string _GetString(PyObject* obj);

  PyObject* _counter;
};
