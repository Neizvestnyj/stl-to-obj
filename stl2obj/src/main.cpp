#include <string>
#include <iostream>

#include "converter.h"

using namespace std;

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

int main(int argc, char** argv)
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
    convert(src, dst, true, &test_callback, vp, NULL);

    return EXIT_SUCCESS;
}