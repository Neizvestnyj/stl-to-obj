# stl-to-obj

## What is it?
It is powerful python tool to convert stl file to obj using c++ in backend and built 
with cython for all platforms

[![PyPI version](https://img.shields.io/pypi/v/stl2obj.svg)](https://pypi.org/project/stl2obj)
[![Documentation Status](https://readthedocs.org/projects/stl-to-obj/badge/?version=latest)](https://stl-to-obj.readthedocs.io/en/latest/?badge=latest)
[![Supported Python versions](https://img.shields.io/pypi/pyversions/stl2obj.svg)](https://badge.fury.io/py/stl2obj)
[![Downloads](https://pepy.tech/badge/stl2obj)](https://pepy.tech/project/stl2obj)
[![Repository size](https://img.shields.io/github/repo-size/Neizvestnyj/stl-to-obj.svg)](https://pypi.python.org/pyp/stl-to-obj)

## Build pure c++
1. Install [CMake](https://cmake.org/install/)
2. Then run
    1. **Winows:** `build.cmd` and in `build\Debug` folder you will find **exe** file
    2. **Linux/macOS:** `sh build.sh` and you will find runnable `stl2obj` in `build` folder
3. In terminal type 
```bash
# Windows
stl2obj.exe <src> <dst>
# Linux/MacOS
./stl2obj <src> <dst>
```
4. Enjoy fast conversion!

## Installation
From [pypi](https://pypi.org/project/stl2obj/)
```bash
pip install stl2obj
```

From [GitHub](https://github.com) directly
```bash
pip install https://github.com/Neizvestnyj/stl-to-obj/archive/master.zip
```
**OR**

if needed `python setup.py clean --all`
```bash
git clone https://github.com/Neizvestnyj/stl-to-obj.git
cd stl-to-obj-master
python setup.py install
```

## Usage
```py
from stl2obj import Stl2Obj

stl = 'path-to-stl-file'
obj = 'path-to-obj-file'
callback = lambda code: print(code)

Stl2Obj().convert(stl, obj, callback)
```

## Usage with [python-for-android](https://github.com/kivy/python-for-android)
### Installation
```bash
pip install buildozer
```

### buildozer.spec
```
requirements = kivy, stl2obj
p4a.local_recipes = <path-to-stl2obj-recipe-folder>
```

**in console**
```bash
buildozer android debug deploy run logcat
```

or just copy *recipes* to *examples/kivy_example* folder and run `buildozer android debug deploy run logcat`

## Usage with [kivy-ios](https://github.com/kivy/kivy-ios)
### Installation

```bash
pip install git+https://github.com/kivy/kivy-ios.git
```

**in console**
```bash
toolchain build python3 kivy
toolchain build stl2obj --add-custom-recipe=recipes/ios/stl2obj
toolchain create Stl-to-obj examples/kivy_example
```

## Authors

[Neizvestnyj](https://github.com/Neizvestnyj), [psychowasp](https://github.com/psychowasp), [Amir Baserinia](https://github.com/baserinia)
