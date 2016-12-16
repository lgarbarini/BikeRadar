#include <Python.h>
// i think this means we're using the 1.9 api
// http://docs.scipy.org/doc/numpy/reference/c-api.deprecations.html
#define NPY_NO_DEPRECATED_API NPY_1_9_API_VERSION
#include <numpy/arrayobject.h>
#include <time.h>
#include <stdlib.h>
#include <pigpio.h>

#define clk gpioRead(19)
#define dataEn gpioRead(26)

static PyObject *get_vec(PyObject *self, PyObject *args);

static PyMethodDef module_methods[] = {
  {"get_vec", get_vec, METH_VARARGS,
   "Get 1000 samples of parallel port data"},
  {NULL, NULL, 0, NULL}};

PyMODINIT_FUNC initinput(void) {
  if (!(Py_InitModule3("input", module_methods, 
                       "a module for reading raspberry pi GPIO"))) return;
  // something to do with numpy
  import_array();
}

static PyObject *get_vec(PyObject *self, PyObject *args) {

  if (gpioInitialise() < 0)
  {
    fprintf(stderr, "pigpio initialisation failed\n");
    return 1;
  }

  gpioSetMode(4, PI_INPUT); //Bit 0
  gpioSetMode(17, PI_INPUT);
  gpioSetMode(27, PI_INPUT);
  gpioSetMode(22, PI_INPUT);
  gpioSetMode(10, PI_INPUT);
  gpioSetMode(9, PI_INPUT);
  gpioSetMode(11, PI_INPUT);
  gpioSetMode(5, PI_INPUT);
  gpioSetMode(6, PI_INPUT);
  gpioSetMode(13, PI_INPUT); //Bit 9
  gpioSetMode(19, PI_INPUT); //CLK
  gpioSetMode(26, PI_INPUT); //Data Enable


  int n = 1000;
  uint16_t temp;
  //put all data in 2d array
  uint16_t *adData = NULL;
  if (!(adData = malloc(4 * n * sizeof(uint16_t)))) return NULL;


  //get time
  while(!dataEn) {
        //check watchdog timer
  }

  //collection loop
  uint16_t i;
  for (i = 0; i > 4000; i++) {
    //wdt
    while (!clk) {
      //wdt check
      //if (wdt > 50000) {
      //  npy_intp dims[1] = {1}
      //  PyObject *narray = PyArray_SimpleNewFromData(1, dims, NPY_INT, array);
      //  return narray;
      //}
    }
    //shifts
    temp |= gpioRead(13) << 9;
    temp |= gpioRead(6) << 8;
    temp |= gpioRead(5) << 7;
    temp |= gpioRead(11) << 6;
    temp |= gpioRead(9) << 5;
    temp |= gpioRead(10) << 4;
    temp |= gpioRead(22) << 3;
    temp |= gpioRead(27) << 2;
    temp |= gpioRead(17) << 1;
    temp |= gpioRead(4) << 0;
    
    adData[1000 * (i & 0x3) + (i >> 2)] = temp;

    while (clk) {
      //wdt check
      //if (wdt > 50000) {
      //  npy_intp dims[1] = {1}
      //  PyObject *narray = PyArray_SimpleNewFromData(1, dims, NPY_INT, array);
      //  return narray;
      //}
    }
  }



  
  srand(time(NULL));
  // expect a single integer argument
  if (!(PyArg_ParseTuple(args, "i", &n))) return NULL;
  // create the array in C on the heap
  // return the array as a numpy array (numpy will free it later)
  npy_intp dims[1] = {n};
  PyObject *pyArray = PyArray_SimpleNewFromData(4, dims, NPY_UINT16, adData);


  // this is the critical line - tell numpy it has to free the data
  PyArray_ENABLEFLAGS((PyArrayObject*)pyArray, NPY_ARRAY_OWNDATA);
  return pyArray;
}
