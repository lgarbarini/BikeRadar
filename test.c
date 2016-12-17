#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pigpio.h>

#define clk gpioRead(19)
#define dataEn gpioRead(26)


void main() {

  if (gpioInitialise() < 0)
  {
    fprintf(stderr, "pigpio initialisation failed\n");
    return 1;
  }

  // gpioSetMode(4, PI_INPUT); //Bit 0
  // gpioSetMode(17, PI_INPUT);
  // gpioSetMode(27, PI_INPUT);
  // gpioSetMode(22, PI_INPUT);
  // gpioSetMode(10, PI_INPUT);
  // gpioSetMode(9, PI_INPUT);
  // gpioSetMode(11, PI_INPUT);
  // gpioSetMode(5, PI_INPUT);
  // gpioSetMode(6, PI_INPUT);
  // gpioSetMode(13, PI_INPUT); //Bit 9
  // gpioSetMode(19, PI_INPUT); //CLK
  // gpioSetMode(26, PI_INPUT); //Data Enable


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
  for (i = 0; i < 4000; i++) {
    //wdt
    //while (!clk) {
      //wdt check
      //if (wdt > 50000) {
      //  npy_intp dims[1] = {1}
      //  PyObject *narray = PyArray_SimpleNewFromData(1, dims, NPY_INT, array);
      //  return narray;
      //}
    //}
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

    // gpioSetPullUpDown(13, PI_PUD_UP);
    // gpioSetPullUpDown(6, PI_PUD_UP);
    // gpioSetPullUpDown(5, PI_PUD_UP);
    // gpioSetPullUpDown(11, PI_PUD_UP);
    // gpioSetPullUpDown(9, PI_PUD_UP);
    // gpioSetPullUpDown(10, PI_PUD_UP);
    // gpioSetPullUpDown(22, PI_PUD_UP);
    // gpioSetPullUpDown(27, PI_PUD_UP);
    // gpioSetPullUpDown(17, PI_PUD_UP);
    // gpioSetPullUpDown(4, PI_PUD_UP);


    adData[1000 * (i & 0x3) + (i >> 2)] = temp;

    //while (clk) {
      //wdt check
      //if (wdt > 50000) {
      //  npy_intp dims[1] = {1}
      //  PyObject *narray = PyArray_SimpleNewFromData(1, dims, NPY_INT, array);
      //  return narray;
      //}
    //}
  }

  for(i = 0; i < 4000; i++) {
    fprintf(stderr,"%d, ", adData[i]);
  }


  return 1;
}
