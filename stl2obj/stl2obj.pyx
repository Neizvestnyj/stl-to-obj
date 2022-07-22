# cython: language_level=3, boundscheck=False
# distutils: language=c++

cdef extern from "string" namespace "std":
    cdef cppclass string:
        char* c_str()

cdef extern from "src/stl2obj.cpp":
    pass

'''
except + mean if the C++ code or the initial memory allocation raises an exception due to a failure, this will let
Cython safely raise an appropriate Python exception
'''

# Redeclare the .h in cython space
cdef extern from "src/stl2obj.h":
    int convert(string src, string dst);
		
'''
simple pure python wrapping
use normal def if your cython code dont need to do anything else but wrapping it
returns double as python object float
'''

# after can be imported after build
def stl_to_ob_convert(str src, str dst):
    return convert(src, dst)  # convert - c++ func
    