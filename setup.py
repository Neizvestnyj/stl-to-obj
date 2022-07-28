from setuptools import setup, Extension

import os
from pathlib import Path
import sys
from os import environ

platform = sys.platform

ndkplatform = environ.get('NDKPLATFORM')
if ndkplatform is not None and environ.get('LIBLINK'):
    platform = 'android'

kivy_ios_root = environ.get('KIVYIOSROOT', None)

if kivy_ios_root is not None:
    platform = 'ios'

can_use_cython = True

extra_compile_args = []
if platform in ('ios', 'android'):
    # NEVER use or declare cython on these platforms
    print('Not using cython on %s' % platform)
    can_use_cython = False
else:
    if platform == 'darwin':
        # but '-std=c++11' is necessary
        extra_compile_args = ['-stdlib=libc++']
    else:
        extra_compile_args = ['-std=c++11']

__version__ = '0.1'
__name__ = 'stl2obj'

current_dir = Path(__file__).absolute().parent
stl2obj_dir = os.path.join(current_dir, __name__)
print(f"{__name__} directory: {stl2obj_dir}")

with open(os.path.join(current_dir, 'requirements.txt')) as req_f:
    requirements = []
    lines = req_f.readlines()

    for line in lines:
        requirements.append(line.replace('\n', '').strip())

cpp_sources = []
path_to_src = os.path.join(stl2obj_dir, 'src')

# check if all files are included
for file in os.listdir(path_to_src):
    name, ext = os.path.splitext(file)

    if ext == '.cpp':
        cpp_sources.append(file)

additional_files = [os.path.join(path_to_src, src) for src in cpp_sources]

extensions = [
    Extension(name=f'{__name__}',
              sources=[f'{stl2obj_dir}/{__name__}.pyx', *additional_files],
              language='c++',
              extra_compile_args=extra_compile_args,
              ),
]

if can_use_cython:
    try:
        from Cython.Build import cythonize
    except (ImportError, ModuleNotFoundError) as import_cython_error:
        sys.exit(
            "Cython not found. Cython is needed to build the extension modules. "
            "Type: `pip install cython` or `pip install -r requirements.txt`"
        )

    ext_modules = cythonize(extensions)
else:
    ext_modules = extensions

setup(name=__name__,
      version=__version__,
      author="Neizvestnyj",
      url=f'https://github.com/Neizvestnyj/stl-to-obj',
      description='C++ std to obj converter for Python',
      platforms=['all'],
      license='GPL-3.0 License',
      keywords=["python c++ cython std2obj"],
      ext_modules=ext_modules,
      install_requires=requirements,
      # Disable zip_safe, because:
      #   - Cython won't find `.pxd` files inside installed .egg, hard to compile libs depending on this one
      #   - dynamic loader may need to have the library unzipped to a temporary directory anyway (at import time)
      zip_safe=False,
      python_requires=">=3.6",
      )
