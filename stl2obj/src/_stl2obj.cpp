#include <cstdio>
#include <cstdlib>
#include <string>

#include "vectornd.h"
#include "geometry.h"
#include "importstl.h"
#include "exportobj.h"
#include "_stl2obj.h"
#include "exists.h"

using namespace std;

void convert(string src, string dst, void(*callback)(int, void*), void* py_object) {
    /*
    src - full path to stl file
    dst - full path to obj file
    */

    int code;
    
    if (is_file_exist(src) == true) { // the best way to check this is in cython
        //  create a geometry tesselation object
        Geometry tessel;

        //  fill up the tesselation object with STL data (load STL)
        tessel.visit(ImportSTL(src));

        //  write down the tesselation object into OBJ file (save OBJ)
        tessel.visit(ExportOBJ(dst));
        code = 0;
    }
    else {
        cout << src << " does not exists" << endl;
        code = 1;
    }

    if (callback && py_object) {
        callback(code, py_object);
    }
}


void test_callback(int code, void* call_object) {
    // just callback, that call other c++ function pointer. In python `call_object` - pointer to python function
    typedef void (*func_ptr)(int);

    void* object_pointer = call_object;
    func_ptr object_func = reinterpret_cast<func_ptr>(object_pointer);
    object_func(code);
}

void test_call_object(int code) {
    cout << "Object callback: " << code << endl;
}

int main(int argc, char **argv)
{   
    string src, dst;
    
    if (argv[0] && argv[1]) {
        src = argv[1];
        dst = argv[2];
    }
    else {
        cout << "You cant pass arguments, using default" << endl;
        src = "F:\\VS\\stl-to-obj\\files\\cube.stl";
        dst = "F:\\VS\\stl-to-obj\\files\\cube.obj";
    }

    cout << src << " will be converted and save as " << dst << endl;

    void* vp = (void*)test_call_object;

    // or you can pass: "", "", NULL, NULL
    convert(src, dst, &test_callback, vp);

    return EXIT_SUCCESS;
}
