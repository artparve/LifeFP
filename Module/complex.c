#include "complex.h"

PyMethodDef complex_methods[] = {
    {NULL, NULL, 0, NULL}
};

PyTypeObject complex_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "Complex",
    .tp_basicsize = sizeof(complex_n),
    //.tp_dealloc = ,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Complex number",
    .tp_methods = complex_methods,
};