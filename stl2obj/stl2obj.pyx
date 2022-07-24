# cython: language_level=3
# distutils: language=c++

from libcpp.string cimport string
from os.path import exists
from pathlib import Path

# Redeclare the .h in cython space
cdef extern from "src/_stl2obj.h":
    int convert(string src, string dst);

'''
simple pure python wrapping
use normal def if your cython code don't need to do anything else but wrapping it
'''

cdef class Stl2Obj:
    def convert(self, src: str, dst: str):
        if not exists(src):
            raise FileNotFoundError(f'{src} does not exists')

        p = Path(dst)

        if not exists(p.parent):
            raise OSError(f'{p.parent} directory does not exist')

        cdef cpp_src = <string>src.encode('utf-8')
        cdef cpp_dst = <string>dst.encode('utf-8')

        return convert(cpp_src, cpp_dst)  # convert - c++ func
