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

#endif