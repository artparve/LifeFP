#include "complex.h"

static PyMethodDef complex_methods[] = {
    {
        "conjugate",
        complex_conjugate,
        METH_VARARGS,
        "Conjugate number"
    },
    {
        "re",
        complex_re,
        METH_VARARGS,
        "Real part of number"
    },
    {
        "im",
        complex_im,
        METH_VARARGS,
        "Imagine part of number"
    },
    {NULL, NULL, 0, NULL},
};

static PyNumberMethods complex_op = {
    .nb_add = complex_sum,
    .nb_subtract = complex_sub,
    .nb_negative = complex_neg,
    .nb_multiply = complex_mul,
    .nb_true_divide = complex_div,
};

PyTypeObject complex_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "Complex",
    .tp_basicsize = sizeof(complex_n),
    .tp_dealloc = (destructor)clean_complex,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Complex number",
    .tp_methods = complex_methods,
    .tp_repr = complex_repr,
    .tp_as_number = &complex_op,
};

void clean_complex(complex_n* self)
{
    Py_XDECREF(self);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

void complex_init(complex_n* c, double re, double im)
{
    c->re = re;
    c->im = im;
}

PyObject* create_complex(PyObject* self, PyObject* args)
{
    double re, im;
    if (!PyArg_ParseTuple(args, "dd", &re, &im))
        return NULL;
    complex_n* c = PyObject_NEW(complex_n, &complex_Type);
    complex_init(c, re, im);
    return (PyObject*)c;
}

PyObject* complex_repr(PyObject* self)
{
    complex_n* c = (complex_n*)self;
    char str[128];
    if (c->im>=0) {
        snprintf(str, 128, "%f + %fI", c->re, c->im);
    } else {
        snprintf(str, 128, "%f - %fI", c->re, -c->im);
    }
    PyObject *repr = PyUnicode_FromString(str);
    return repr;
}

PyObject* complex_re(PyObject* self)
{
    complex_n* c = (complex_n*)self;
    return Py_BuildValue("d", c->re);
}

PyObject* complex_im(PyObject* self)
{
    complex_n* c = (complex_n*)self;
    return Py_BuildValue("d", c->im);
}

PyObject* complex_sum(PyObject* self, PyObject* another)
{
    double re, im;
    const char* st = another->ob_type->tp_name;
    if (strcmp("int", st)==0) {
        int s = PyLong_AsLong(another);
        re = ((complex_n*)self)->re + s;
        im = ((complex_n*)self)->im;
    } else if (strcmp("float", st)==0) {
        double s = PyFloat_AsDouble(another);
        re = ((complex_n*)self)->re + s;
        im = ((complex_n*)self)->im;
    } else {
        re = ((complex_n*)self)->re + ((complex_n*)another)->re;
        im = ((complex_n*)self)->im + ((complex_n*)another)->im;
    }
    return create_complex(self, Py_BuildValue("(dd)", re, im));
}

PyObject* complex_sub(PyObject* self, PyObject* another)
{
    double re, im;
    const char* st = another->ob_type->tp_name;
    if (strcmp("int", st)==0) {
        int s = PyLong_AsLong(another);
        re = ((complex_n*)self)->re - s;
        im = ((complex_n*)self)->im;
    } else if (strcmp("float", st)==0) {
        double s = PyFloat_AsDouble(another);
        re = ((complex_n*)self)->re - s;
        im = ((complex_n*)self)->im;
    } else {
        re = ((complex_n*)self)->re - ((complex_n*)another)->re;
        im = ((complex_n*)self)->im - ((complex_n*)another)->im;
    }
    return create_complex(self, Py_BuildValue("(dd)", re, im));
}

PyObject* complex_neg(PyObject* self)
{
    double re = ((complex_n*)self)->re;
    double im = ((complex_n*)self)->im;
    return create_complex(self, Py_BuildValue("(dd)", -re, -im));
}

PyObject* complex_conjugate(PyObject* self)
{
    double re = ((complex_n*)self)->re;
    double im = ((complex_n*)self)->im;
    return create_complex(self, Py_BuildValue("(dd)", re, -im));
}

PyObject* complex_mul(PyObject* self, PyObject* another)
{
    double re, im;
    const char* st = another->ob_type->tp_name;
    if (strcmp("int", st)==0) {
        int s = PyLong_AsLong(another);
        re = ((complex_n*)self)->re * s;
        im = ((complex_n*)self)->im * s;
    } else if (strcmp("float", st)==0) {
        double s = PyFloat_AsDouble(another);
        re = ((complex_n*)self)->re * s;
        im = ((complex_n*)self)->im * s;
    } else {
        double re1 = ((complex_n*)self)->re, re2 = ((complex_n*)another)->re;
        double im1 = ((complex_n*)self)->im, im2 = ((complex_n*)another)->im;
        re = re1*re2 - im1*im2;
        im = re1*im2 + re2*im1;
    }
    return create_complex(self, Py_BuildValue("(dd)", re, im));
}

PyObject* complex_div(PyObject* self, PyObject* another)
{
    double re, im;
    const char* st = another->ob_type->tp_name;
    if (strcmp("int", st)==0) {
        int s = PyLong_AsLong(another);
        re = ((complex_n*)self)->re / s;
        im = ((complex_n*)self)->im / s;
    } else if (strcmp("float", st)==0) {
        double s = PyFloat_AsDouble(another);
        re = ((complex_n*)self)->re / s;
        im = ((complex_n*)self)->im / s;
    } else {
        double re1 = ((complex_n*)self)->re, re2 = ((complex_n*)another)->re;
        double im1 = ((complex_n*)self)->im, im2 = ((complex_n*)another)->im;
        double abs2  = re2*re2 + im2*im2;
        re = (re1*re2 + im1*im2)/abs2;
        im = (-re1*im2 + re2*im1)/abs2;
    }
    return create_complex(self, Py_BuildValue("(dd)", re, im));
}