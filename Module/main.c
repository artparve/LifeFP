#include "main.h"

static PyMethodDef own_methods[] = {
    {NULL, NULL, 0, NULL}
};

static PyModuleDef simple_module = {
    PyModuleDef_HEAD_INIT,
    "complex_numbers",
    "doc",
    -1,
    own_methods
};

PyMODINIT_FUNC PyInit_complex_numbers(void)
{
    PyObject* module;
    module = PyModule_Create(&simple_module);
    if (module==NULL)
        return NULL;
    return module;
}


