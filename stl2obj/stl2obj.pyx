# cython: language_level=3
# distutils: language=c++

cdef extern from "string" namespace "std":
    cdef cppclass string:
        char* c_str()

cdef extern from "src/stl2obj.cpp":
    pass

# Redeclare the .h in cython space
cdef extern from "src/stl2obj.h":
    int convert(string src, string dst);
		
'''
simple pure python wrapping
use normal def if your cython code don't need to do anything else but wrapping it
'''

# after can be imported after build
def stl_to_obj_convert(str src, str dst):
    return convert(src, dst)  # convert - c++ func
