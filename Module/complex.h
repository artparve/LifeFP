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
PyObject* complex_repr(PyObject* self);

PyObject* complex_re(PyObject* self);
PyObject* complex_im(PyObject* self);
PyObject* complex_sum(PyObject* self, PyObject* another);
PyObject* complex_sub(PyObject* self, PyObject* another);
PyObject* complex_neg(PyObject* self);

#endif