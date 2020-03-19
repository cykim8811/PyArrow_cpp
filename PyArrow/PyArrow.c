#include <Python.h>

/*
 * Implements an example function.
 */
PyDoc_STRVAR(PyArrow_example_doc, "example(obj, number)\
\
Example function");

PyObject *PyArrow_example(PyObject *self, PyObject *args, PyObject *kwargs) {
    /* Shared references that do not need Py_DECREF before returning. */
    PyObject *obj = NULL;
    int number = 0;

    /* Parse positional and keyword arguments */
    static char* keywords[] = { "obj", "number", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi", keywords, &obj, &number)) {
        return NULL;
    }

    /* Function implementation starts here */

    if (number < 0) {
        PyErr_SetObject(PyExc_ValueError, obj);
        return NULL;    /* return NULL indicates error */
    }

    Py_RETURN_NONE;
}

/*
 * List of functions to add to PyArrow in exec_PyArrow().
 */
static PyMethodDef PyArrow_functions[] = {
    { "example", (PyCFunction)PyArrow_example, METH_VARARGS | METH_KEYWORDS, PyArrow_example_doc },
    { NULL, NULL, 0, NULL } /* marks end of array */
};

/*
 * Initialize PyArrow. May be called multiple times, so avoid
 * using static state.
 */
int exec_PyArrow(PyObject *module) {
    PyModule_AddFunctions(module, PyArrow_functions);

    PyModule_AddStringConstant(module, "__author__", "cykim");
    PyModule_AddStringConstant(module, "__version__", "1.0.0");
    PyModule_AddIntConstant(module, "year", 2020);

    return 0; /* success */
}

/*
 * Documentation for PyArrow.
 */
PyDoc_STRVAR(PyArrow_doc, "The PyArrow module");


static PyModuleDef_Slot PyArrow_slots[] = {
    { Py_mod_exec, exec_PyArrow },
    { 0, NULL }
};

static PyModuleDef PyArrow_def = {
    PyModuleDef_HEAD_INIT,
    "PyArrow",
    PyArrow_doc,
    0,              /* m_size */
    NULL,           /* m_methods */
    PyArrow_slots,
    NULL,           /* m_traverse */
    NULL,           /* m_clear */
    NULL,           /* m_free */
};

PyMODINIT_FUNC PyInit_PyArrow() {
    return PyModuleDef_Init(&PyArrow_def);
}
