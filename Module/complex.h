#ifndef COMPLEX_H
#define COMPLEX_H

#include <Python.h>
#include "math.h"
#define M_PI 3.14159265358979323846

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
PyObject* complex_conjugate(PyObject* self);
PyObject* complex_mul(PyObject* self, PyObject* another);
PyObject* complex_div(PyObject* self, PyObject* another);
PyObject* complex_abs(PyObject* self, PyObject* args);
PyObject* complex_arg(PyObject* self, PyObject* args);
PyObject* complex_pow(PyObject* self, PyObject* args);
double _complex_arg(double re, double im);
double _complex_abs(double re, double im);
PyObject* complex_trig_repr(PyObject* self);
PyObject* complex_copy(PyObject* self);

#endif