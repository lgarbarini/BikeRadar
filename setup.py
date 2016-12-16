from distutils.core import setup, Extension
from numpy.distutils.misc_util import get_numpy_include_dirs

setup(ext_modules=[Extension("input", ["input.c"])],
      include_dirs=[get_numpy_include_dirs(), 'lpigpio', 'lrt'])
