# cython: language_level=3
# distutils: language=c++
from kivy.uix._events import EventDispatcher


from libcpp.string cimport string


# Redeclare the .h in cython space
cdef extern from "src/_stl2obj.h":

    int convert(string src, string dst);
		
'''
simple pure python wrapping
use normal def if your cython code don't need to do anything else but wrapping it
'''

cdef class Stl2Obj:

    cdef string _src

    cdef string _dst

    def __cinit__(self):

        self._src = b""
        self._dst = b""

    @property
    def src(self)

    def convert(self):

        print("converting stl to obj - new test")

        return convert(self._src, self._dst)  # convert - c++ func

