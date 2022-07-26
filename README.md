# stl-to-obj

### What is it?
It is powerful python tool to convert stl file to obj using c++ in backend and built 
with cython for all platforms

### Build pure c++
1) Install [CMake](https://cmake.org/install/).
2) Then run `build.cmd` for **Windows** and in `build\Debug` folder you will find **exe** file
or run `sh build.sh` for **Linux/macOS** and you find will runnable `stl2obj` in `build` folder.
3) In terminal type 
```bash
# Windows
stl2obj.exe <src> <dst>
# Linux/MacOS
./stl2obj <src> <dst>
```
4) Enjoy fast conversion!

### Installation
From [pypi](https://pypi.org/project/stl-obj-convertor/)
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

### Usage
```py
from stl2obj import Stl2Obj

stl = 'path-to-stl-file'
obj = 'path-to-obj-file'
callback = lambda code: print(code)

Stl2Obj().convert(stl, obj, callback)
```

### Usage with [python-for-android](https://github.com/kivy/python-for-android)
**buildozer.spec**
```
requirements = kivy, stl2obj
p4a.local_recipes = <path-to-stl2obj-recipe-folder>
```

```bash
buildozer android debug deploy run logcat
```

or just copy *recipes* to *examples/kivy_example* folder and run `buildozer android debug deploy run logcat`

### Authors

[Neizvestnyj](https://github.com/Neizvestnyj), [psychowasp](https://github.com/psychowasp), [Amir Baserinia](https://github.com/baserinia)