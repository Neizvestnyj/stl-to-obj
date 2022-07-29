#include <cstdio>
#include <cstdlib>
#include <string>

#include "vectornd.h"
#include "geometry.h"
#include "importstl.h"
#include "exportobj.h"
#include "converter.h"

using namespace std;

void convert(
    string src, 
    string dst, 
    bool debug = true,
    void(*callback)(int, void*) = NULL, 
    void* py_callback = NULL, 
    void* py_progress = NULL) {
    /*
    `src` - full path to stl file
    `dst` - full path to obj file
    `callback` - just function, that call pointer like `py_object`
    */

    if (debug == false) {
        streambuf* old = cout.rdbuf();
        cout.rdbuf(0);
    } 

    int code;

    //  create a geometry tesselation object
    Geometry tessel;

    //  fill up the tesselation object with STL data (load STL)
    tessel.visit(ImportSTL(src, callback, py_progress));

    //  write down the tesselation object into OBJ file (save OBJ)
    tessel.visit(ExportOBJ(dst));

    code = 0;

    if (callback && py_callback) {
        // for python lib `callback` written in c, `py_object` - pointer to python function
        callback(code, py_callback);
    }
}

// only for example
void test_callback(int code, void* call_object) {
    // just callback, that call other c++ function pointer. In python `call_object` - pointer to python function

    typedef void (*func_ptr)(int);

    void* object_pointer = call_object;
    func_ptr object_func = reinterpret_cast<func_ptr>(object_pointer);
    object_func(code);
}

// only for example
void test_call_object(int code) {
    cout << "Object callback: " << code << endl;
}

void test_py_progress(int value) {
    cout << value << " ";
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

    void* vp = (void*)test_call_object; // void pointer
    void* vpp = (void*)test_py_progress; //void progress pointer

    // convert(src, dst, &test_callback, vp, vpp);
    convert(src, dst, true, &test_callback, vp);

    return EXIT_SUCCESS;
}
