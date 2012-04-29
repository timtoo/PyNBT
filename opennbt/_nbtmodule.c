#include <Python.h>
#include "structmember.h"

/* Implements the OpenNBT types using the Python C API,
 * offering an exponential speed increase in most cases.
 *
 * Copyright (c) 2012 Tyler Kennedy <tk@tkte.ch>
 *
 * As an exception to the MIT licence that covers OpenNBT,
 * public attribution (such as an "About Page") is required
 * if this compiled module is used. You may use the
 * pure-python implementation without this exception.
 */

/* --------------------------->
 * BaseTag
 */

typedef struct {
    PyObject_HEAD
    PyObject *name;
    PyObject *value;
} BaseTag;

static void
BaseTag_dealloc(BaseTag *self)
{
    Py_XDECREF(self->name);
    Py_XDECREF(self->value);
    self->ob_type->tp_free((PyObject*)self);
}

static PyObject * 
BaseTag_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    BaseTag *self;

    self = (BaseTag*)type->tp_alloc(type, 0);
    if(self != NULL) {
        self->name = Py_None;
        Py_INCREF(Py_None);
        self->value = Py_None;
        Py_INCREF(Py_None);
    }

    return (PyObject *)self;
}

static int
BaseTag_init(BaseTag *self, PyObject *args, PyObject *kwds)
{
    PyObject *name=NULL, *value=NULL, *tmp;
    static char *kwlist[] = {"value", "name", NULL};

    if(!PyArg_ParseTupleAndKeywords(args, kwds, "O|S", kwlist, &value, &name))
        return -1;

    if(name) {
        tmp = self->name;
        Py_INCREF(name);
        self->name = name;
        Py_DECREF(tmp);
    }

    tmp = self->value;
    Py_INCREF(value);
    self->value = value;
    Py_DECREF(tmp);

    return 0;
}

static PyMemberDef BaseTag_members[] = {
    {"name", T_OBJECT_EX, offsetof(BaseTag, name), 0, ""},
    {"value", T_OBJECT_EX, offsetof(BaseTag, value), 0, ""},
    {NULL}
};

static PyMethodDef  BaseTag_methods[] = {
    {NULL}
};

static PyTypeObject BaseTagType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "_nbt.BaseTag",             /*tp_name*/
    sizeof(BaseTag),             /*tp_basicsize*/
    0,                          /*tp_itemsize*/
    (destructor)BaseTag_dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "TODO DOCSTRING",           /* tp_doc */
    0,                     /* tp_traverse */
    0,                     /* tp_clear */
    0,                     /* tp_richcompare */
    0,                     /* tp_weaklistoffset */
    0,                     /* tp_iter */
    0,                     /* tp_iternext */
    BaseTag_methods,             /* tp_methods */
    BaseTag_members,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)BaseTag_init,      /* tp_init */
    0,                         /* tp_alloc */
    BaseTag_new,                 /* tp_new */
};

/* --------------------------->
 * 
 */

static PyMethodDef module_methods[] = {
    {NULL}
};

#ifndef PyMODINIT_FUNC
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC
init_nbt(void)
{
    PyObject* m;
    if(PyType_Ready(&BaseTagType) < 0)
        return;

    m = Py_InitModule3("_nbt", module_methods, "TODO DOCSTRING");
    if(m == NULL)
        return;

    Py_INCREF(&BaseTagType);
    PyModule_AddObject(m, "BaseTag", (PyObject *)&BaseTagType);
}