from distutils.core import setup, Extension
from numpy.distutils.misc_util import get_numpy_include_dirs

setup(ext_modules=[Extension(
            "input", 
            ["input.c"],
            libraries = ['pigpio','rt'],
            library_dirs = ['/usr/local/lib']
      )],
      include_dirs=[get_numpy_include_dirs()])
