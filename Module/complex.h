#ifndef COMPLEX_H
#define COMPLEX_H

#include <Python.h>

typedef struct
{
    PyObject_HEAD
    double re;
    double im;
} complex_n;

PyTypeObject complex_Type;
void clean_complex(complex_n* self);
void complex_init(complex_n* c, double re, double im);
PyObject* create_complex(PyObject* self, PyObject* args);
PyObject* print_complex(PyObject* self, PyObject* args);
#endif