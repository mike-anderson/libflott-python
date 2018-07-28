/*
 * Libflott Python Binding
 * Copyright 2018 Michael Anderson
 *                University of Victoria
 * 
 * Binds Libflott
 * Copyright 2012 Niko Rebenich and Stephen Neville,
 *                University of Victoria
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <Python.h>
#include "libflott/flott.h"

typedef enum flott_action flott_action;
enum flott_action {
  FLOTT_NTI_DIST    = 0,
  FLOTT_NTC_DIST    = 1,
};

double flott_python_nti_ntc_dist (char* input_a, char *input_b, flott_action action) {

  flott_source *source;
  double ret_val = -1.0;
  flott_object *op = flott_create_instance (2 + (int)action);
  if (op == NULL) { 
    return -1.0;
  }
  
  /* set default flott options */
  op->verbosity_level = FLOTT_VL_QUIET; //< suppress all errors on stdout/stderr
  if (action == FLOTT_NTI_DIST) {
    op->input.append_termchar = false;
  } else {
    op->input.append_termchar = true;
  }

  /* set source */
  source = &(op->input.source[0]);
  source->length = strlen(input_a);
  source->storage_type = FLOTT_DEV_MEM;
  source->data.bytes = input_a;

  source = &(op->input.source[1]);
  source->length = strlen(input_b);
  source->storage_type = FLOTT_DEV_MEM;
  source->data.bytes = input_b;

  if (action == FLOTT_NTI_DIST) {
    /* compute normalized_t_information_distance */
    if (flott_nti_dist(op, &ret_val) != FLOTT_SUCCESS) {
      return -1.0;
    };
  } else {
    /* compute normalized_t_complexity_distance */
    if (flott_ntc_dist(op, &ret_val) != FLOTT_SUCCESS) {
      return -1.0;
    };  
  }

  flott_destroy (op); //< clean-up

  return ret_val;
}

static PyObject* nti_dist(PyObject* self, PyObject* args) {

  char* input_a; char* input_b;
  if (!PyArg_ParseTuple(args, "ss", &input_a, &input_b)) {
    return NULL;
  }

  return Py_BuildValue("d", 
    flott_python_nti_ntc_dist(input_a, input_b, FLOTT_NTI_DIST)
  );

}

static PyObject* ntc_dist(PyObject* self, PyObject* args) {

  char* input_a; char* input_b;
  if (!PyArg_ParseTuple(args, "ss", &input_a, &input_b)) {
    return NULL;
  }

  return Py_BuildValue("d", 
    flott_python_nti_ntc_dist(input_a, input_b, FLOTT_NTC_DIST)
  );

}

static PyMethodDef flott_methods[] = {
  {"nti_dist", nti_dist, METH_VARARGS, 
   "compute the t-information distance between two strings"},
  {"ntc_dist", ntc_dist, METH_VARARGS, 
   "compute the t-complexity distance between two strings"},
  { NULL, NULL, 0, NULL }
};

static struct PyModuleDef flott = {
    PyModuleDef_HEAD_INIT,
    "flott",
    "Lib Flott",
    -1,
    flott_methods
};

PyMODINIT_FUNC PyInit_flott(void)
{
    Py_Initialize();
    return PyModule_Create(&flott);
}