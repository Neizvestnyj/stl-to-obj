# cython: language_level=3
# distutils: language=c++

from libcpp.string cimport string
from libcpp cimport bool

from os.path import exists
from pathlib import Path

# Redeclare the .h in cython space
cdef extern from "src/converter.h":
    void convert(
        string src,
        string dst,
        bool debug,
        void(*callback)(int, void*),
        void* py_object,
        void* py_progress
        ) nogil #your .h and .cpp must be like this also

# c callback to call python callback
cdef void c_callback(int result, void* py_object) with gil:
    # or (<object>py_object)(result)
    cdef object func = <object>py_object

    # check if func is not None
    if func:
        func(result)

cdef class Stl2Obj:
    def convert(self,
                src: str,
                dst: str,
                debug: bool = True,
                callback: object = None,
                progress_callback: object = None):
        if not exists(src):
            raise FileNotFoundError(f'{src} does not exists')

        p = Path(dst)

        if not exists(p.parent):
            raise OSError(f'{p.parent} directory does not exist')

        cdef string cpp_src = <string>src.encode('utf-8')
        cdef string cpp_dst = <string>dst.encode('utf-8')
        cdef bool cpp_debug = <bool>debug

        """
        converts python object to `void*`
        everything in python is a Object, even `None`
        so if you pass `None` as object and it converts it to `void*`
        then your callback must check it.
        Look in -> `cdef void c_callback(int result, void* py_object) with gil:`
        """
        cdef void* callback_ptr = <void*>callback
        cdef void* progress_ptr = <void*>progress_callback

        with nogil:
            convert(cpp_src, cpp_dst, cpp_debug, c_callback, callback_ptr, progress_ptr)
