#include "complex.h"

PyMethodDef complex_methods[] = {
    {NULL, NULL, 0, NULL},
};

PyNumberMethods complex_op = {
    .nb_add = complex_sum,
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
    snprintf(str, 128, "%f + %fI", c->re, c->im);
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
    double re = ((complex_n*)self)->re + ((complex_n*)another)->re;
    double im = ((complex_n*)self)->im + ((complex_n*)another)->im;
    return create_complex(self, Py_BuildValue("(dd)", re, im));
}