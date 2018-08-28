from distutils.core import setup, Extension

ext = Extension('cysort', ['cysort.c'],
 				extra_compile_args=['-fopenmp'], 
 				extra_link_args=['-lgomp'])

setup(name='cysort', version='0.1', ext_modules=[ext])