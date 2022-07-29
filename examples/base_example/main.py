from stl2obj import Stl2Obj
import os
import pathlib

current_folder = os.path.join(pathlib.Path(__file__).parent.resolve())

stl = os.path.join(current_folder, 'cube.stl')
obj = os.path.join(current_folder, 'cube.obj')
a = Stl2Obj()
a.convert(stl, obj)
