# stl-to-obj

### What is it?
It is powerful python tool to convert stl file to obj using c++ in backend and built 
with cython for all platforms

### Build pure c++
1) Install [CMake](https://cmake.org/install/). 
2) Uncomment `int main` function in **stl2obj/src/stl2obj.cpp** 
3) In this function change full path to *stl* and *obj* file, it will
be something like 
`convert("<PATH-TO-stl-to-obj-master>/files/cube.stl", "<PATH-TO-stl-to-obj-master>/files/cube.obj");`. 
   * **Note**: if you are on **Windows**, replace `/` to `//` in the path. 
4) Then run `build.cmd` for **Windows** and in `build\Debug` folder you will find **exe** file
or run `sh build.sh` for **Linux/macOS** and you find will runnable `stl2obj` in `build` folder.
5) In terminal type 
```bash
# Windows
stl2obj.exe
# Linux/MacOS
./stl2obj
```
6) Enjoy fast conversion!
