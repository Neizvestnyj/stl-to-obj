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


    def __init__(self, src, dst):
        ...
        

    def convert(self, src, dst):

        cdef cpp_src = <string>src.encode('utf-8')
        cdef cpp_dst = <string>dst.encode('utf-8')

        return convert(cpp_src, cpp_dst)  # convert - c++ func

