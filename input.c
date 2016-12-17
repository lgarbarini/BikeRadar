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

static PyObject *get_vec(PyObject *self);
static PyObject *setup(PyObject *self);


static PyMethodDef module_methods[] = {
  {"get_vec", get_vec, 0,
   "Get 1000 samples of parallel port data"},
  {"setup", setup, 0,
  "Setup GPIO"},
  {NULL, NULL, 0, NULL}};

PyMODINIT_FUNC initinput(void) {
  if (!(Py_InitModule3("input", module_methods, 
                       "a module for reading raspberry pi GPIO"))) return;
  // something to do with numpy
  import_array();
}

static PyObject *setup(PyObject *self) {

  if (gpioInitialise() < 0)
  {
    fprintf(stderr, "pigpio initialisation failed\n");
    return NULL;
  }
  gpioSetPullUpDown(13, PI_PUD_UP);
  gpioSetPullUpDown(6, PI_PUD_UP);
  gpioSetPullUpDown(5, PI_PUD_UP);
  gpioSetPullUpDown(11, PI_PUD_UP);
  gpioSetPullUpDown(9, PI_PUD_UP);
  gpioSetPullUpDown(10, PI_PUD_UP);
  gpioSetPullUpDown(22, PI_PUD_UP);
  gpioSetPullUpDown(27, PI_PUD_UP);
  gpioSetPullUpDown(17, PI_PUD_UP);
  gpioSetPullUpDown(4, PI_PUD_UP);

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

  return Py_BuildValue("");
}

static PyObject *get_vec(PyObject *self) {

  if (gpioInitialise() < 0)
  {
    fprintf(stderr, "pigpio initialisation failed\n");
    return NULL;
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

  gpioSetPullUpDown(13, PI_PUD_UP);
  gpioSetPullUpDown(6, PI_PUD_UP);
  gpioSetPullUpDown(5, PI_PUD_UP);
  gpioSetPullUpDown(11, PI_PUD_UP);
  gpioSetPullUpDown(9, PI_PUD_UP);
  gpioSetPullUpDown(10, PI_PUD_UP);
  gpioSetPullUpDown(22, PI_PUD_UP);
  gpioSetPullUpDown(27, PI_PUD_UP);
  gpioSetPullUpDown(17, PI_PUD_UP);
  gpioSetPullUpDown(4, PI_PUD_UP);

  int n = 1000;
  uint16_t temp;
  //put all data in 2d array
  uint16_t *adData = NULL;
  if (!(adData = malloc(4 * n * sizeof(uint16_t)))) return NULL;


  //get time
  // while(!dataEn) {
  //       //check watchdog timer
  // }

  //collection loop
  uint16_t i;
  for (i = 0; i < (n * 4); i++) {
    temp = 0;
    //wdt
    // while (!clk) {
    //   //wdt check
    //   //if (wdt > 50000) {
    //   //  npy_intp dims[1] = {1}
    //   //  PyObject *narray = PyArray_SimpleNewFromData(1, dims, NPY_INT, array);
    //   //  return narray;
    //   //}
    // }
    //shifts
    temp |= (gpioRead(13) & 0x1) << 9;
    temp |= (gpioRead(6) & 0x1) << 8;
    temp |= (gpioRead(5) & 0x1) << 7;
    temp |= (gpioRead(11) & 0x1) << 6;
    temp |= (gpioRead(9) & 0x1) << 5;
    temp |= (gpioRead(10) & 0x1) << 4;
    temp |= (gpioRead(22) & 0x1) << 3;
    temp |= (gpioRead(27) & 0x1) << 2;
    temp |= (gpioRead(17) & 0x1) << 1;
    temp |= (gpioRead(4) & 0x1) << 0;
    
    adData[1000 * (i & 0x3) + (i >> 2)] = temp;

    // while (clk) {
    //   //wdt check
    //   //if (wdt > 50000) {
    //   //  npy_intp dims[1] = {1}
    //   //  PyObject *narray = PyArray_SimpleNewFromData(1, dims, NPY_INT, array);
    //   //  return narray;
    //   //}
    // }
  }
  
  
  // expect a single integer argument
  // create the array in C on the heap
  // return the array as a numpy array (numpy will free it later)
  int dims[1] = {n * 4};
  PyObject *pyArray = PyArray_SimpleNewFromData(1, dims, NPY_UINT16, adData);

  


  // this is the critical line - tell numpy it has to free the data
  PyArray_ENABLEFLAGS((PyArrayObject*)pyArray, NPY_ARRAY_OWNDATA);
  return pyArray;
}
