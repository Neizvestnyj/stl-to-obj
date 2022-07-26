from stl2obj import Stl2Obj
import os

stl = os.path.join('cube.stl')
obj = os.path.join('cube.obj')
a = Stl2Obj()
a.convert(stl, obj)
