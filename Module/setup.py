from distutils.core import setup, Extension

module1 = Extension(
    'complex_numbers',
    sources=['main.c', 'complex.c']
)

setup(
    name='complex_numbers',
    version='1.0',
    description='',
    ext_modules=[module1]
)
