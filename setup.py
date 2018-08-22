from distutils.core import setup, Extension
setup(name='cysort', version='0.1', ext_modules=[Extension('cysort', ['sorts.c'])])