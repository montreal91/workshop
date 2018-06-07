
#include <iostream>
#include <string>

#include <python3.5m/Python.h>

static std::string get_string(PyObject* obj) {
  PyObject* repr = PyObject_Repr(obj);
  PyObject* str = PyUnicode_AsEncodedString(repr, "utf-8", "~E~");
  const char* bytes = PyBytes_AS_STRING(str);

  Py_XDECREF(repr);
  Py_XDECREF(str);
  return std::string(bytes);
}

static void reprint(PyObject* obj) {
  std::cout << get_string(obj) << "\n";
}

int
main(int argc, char *argv[]) {
  PyObject *pName, *pModule, *pDict, *pFunc;
  PyObject *pArgs, *pValue;

  if (argc < 3) {
    fprintf(stderr, "Usage: call pythonfile funcname [args]\n");
    return 1;
  }

  wchar_t *program = Py_DecodeLocale(argv[0], NULL);
  if (program == NULL) {
    fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
    exit(1);
  }
  Py_SetProgramName(program);
  Py_Initialize();
  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path.append(\".\")");
  pName = PyUnicode_DecodeFSDefault(argv[1]);

  pModule = PyImport_Import(pName);
  Py_DECREF(pName);

  if (pModule != NULL) {
    pFunc = PyObject_GetAttrString(pModule, argv[2]);

    if (pFunc && PyCallable_Check(pFunc)) {
      pArgs = PyTuple_New(argc - 3);
      for (int i = 0; i < argc - 3; i++) {
        pValue = Py_BuildValue("s", argv[i+3]);
        if (!pValue) {
          Py_DECREF(pArgs);
          Py_DECREF(pModule);
          fprintf(stderr, "Cannot convert argument!\n");
          return 1;
        }
        // pValue reference stolen here:
        PyTuple_SetItem(pArgs, i, pValue);
      }
      pValue = PyObject_CallObject(pFunc, pArgs);
      Py_DECREF(pArgs);
      if (pValue != NULL) {
        reprint(pValue);
        Py_DECREF(pValue);
      }
      else {
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        PyErr_Print();
        fprintf(stderr, "Call failed\n");
        return 1;
      }
    }
    else {
      if (PyErr_Occurred()) {
        PyErr_Print();
      }
      fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
    }
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);
  }
  else {
    PyErr_Print();
    fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
    return 1;
  }
  Py_Finalize();
  return 0;
}
