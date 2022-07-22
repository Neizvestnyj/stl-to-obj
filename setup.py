from setuptools import setup, Extension

import sys
import os
from pathlib import Path
import platform

try:
    from Cython.Build import cythonize
except (ImportError, ModuleNotFoundError) as import_cython_error:
    sys.exit(
        "Cython not found. Cython is needed to build the extension modules. "
        "Type: `pip install cython` or `pip install -r requirements.txt`"
    )

__version__ = '0.1'
__name__ = 'stl2obj'

current_dir = Path(__file__).absolute().parent
stl2obj_dir = os.path.join(current_dir, __name__)
print(f"{__name__} directory: {stl2obj_dir}")

if platform.system() in ['Windows']:
    extra_compile_args = []
else:
    extra_compile_args = ['-std=c++11', '-ljpeg', '-lpng']

with open(os.path.join(current_dir, 'requirements.txt')) as req_f:
    requirements = []
    lines = req_f.readlines()

    for line in lines:
        requirements.append(line.replace('\n', '').strip())

extensions = [
    Extension(f'{__name__}', [f'{stl2obj_dir}/{__name__}.pyx']),
]

for e in extensions:
    e.cython_directives = {'language_level': "3"}  # all are Python-3
    e.language = "c++"

setup(name=__name__,
      version=__version__,
      author="Neizvestnyj",
      url=f'https://github.com/Neizvestnyj/{__name__}',
      description='C++ std to obj converter for Python',
      platforms=['all'],
      license='GPL-3.0 License',
      keywords=["python c++ cython std2obj"],
      # it is necessary to add f`{__name__}/__init__.py` to the package folder
      packages=[__name__],
      ext_modules=cythonize(extensions),
      install_requires=requirements,
      # Disable zip_safe, because:
      #   - Cython won't find `.pxd` files inside installed .egg, hard to compile libs depending on this one
      #   - dynamic loader may need to have the library unzipped to a temporary directory anyway (at import time)
      zip_safe=False,
      python_requires=">=3.8",
      )
