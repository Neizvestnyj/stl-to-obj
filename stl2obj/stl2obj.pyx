# cython: language_level=3
# distutils: language=c++

from libcpp.string cimport string

# Redeclare the .h in cython space
cdef extern from "src/_stl2obj.h":

    int convert(string src, string dst);

'''
simple pure python wrapping
use normal def if your cython code don't need to do anything else but wrapping it
'''

cdef class Stl2Obj:

    cdef string src

    cdef string dst

    def __init__(self, src, dst):

        self.src = <string>src.encode('utf-8')
        self.dst = <string>dst.encode('utf-8')

    def convert(self):

        print("converting stl to obj - new test")

        return convert(self.src, self.dst)  # convert - c++ func

