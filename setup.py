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

if platform.system() == 'Windows':
    extra_compile_args = []
elif platform.system() == 'Darwin':
    extra_compile_args = ['-std=c++11', '-stdlib=libc++']
else:
    extra_compile_args = ['-std=c++11']

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

setup(name=__name__,
      version=__version__,
      author="Neizvestnyj",
      url=f'https://github.com/Neizvestnyj/stl-to-obj',
      description='C++ std to obj converter for Python',
      platforms=['all'],
      license='GPL-3.0 License',
      keywords=["python c++ cython std2obj"],
      ext_modules=cythonize(extensions),
      install_requires=requirements,
      include_package_data=True,
      # Disable zip_safe, because:
      #   - Cython won't find `.pxd` files inside installed .egg, hard to compile libs depending on this one
      #   - dynamic loader may need to have the library unzipped to a temporary directory anyway (at import time)
      zip_safe=False,
      python_requires=">=3.6",
      )
