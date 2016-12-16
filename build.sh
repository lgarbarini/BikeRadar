#!/bin/bash

rm -fr build
rm -f input.so
python2 setup.py build_ext --inplace
python2 test.py
