from distutils.core import setup, Extension

flott = Extension('flott',
                  include_dirs = ['libflott'],
                  sources = ['flott_python.c',
                             'libflott/flott_lang.c',
                             'libflott/flott_math.c',
                             'libflott/flott_nid.c',
                             'libflott/flott_output.c',
                             'libflott/flott_term.c',
                             'libflott/flott_util.c',
                             'libflott/flott.c',
                             'libflott/main.c'])

setup(name = 'flott', 
      version = '1.0',  \
      ext_modules = [flott])