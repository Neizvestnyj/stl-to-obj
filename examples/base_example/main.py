from stl2obj import Stl2Obj
import os
import pathlib

current_folder = os.path.join(pathlib.Path(__file__).parents[2].resolve(), 'files')

src = os.path.join(current_folder, 'cube.stl')
dst = os.path.join(current_folder, 'cube.obj')
a = Stl2Obj()
a.convert(src, dst)
