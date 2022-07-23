# cython: language_level=3
# distutils: language=c++

from libcpp.string cimport string


# Redeclare the .h in cython space
cdef extern from "src/_stl2obj.h":

    int convert(string& src, string& dst);
		
'''
simple pure python wrapping
use normal def if your cython code don't need to do anything else but wrapping it
'''

def stl_to_ob_convert(str src, str dst):

    print("converting stl to obj")

    cdef string cpp_src = <string>src.encode('utf-8')
    cdef string cpp_dst = <string>dst.encode('utf-8')


    return convert(cpp_src, cpp_dst)  # convert - c++ func

