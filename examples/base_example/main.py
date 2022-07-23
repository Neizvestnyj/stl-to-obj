from stl2obj import Stl2Obj
import os
import pathlib

files_folder = os.path.join(pathlib.Path(__file__).parent.resolve().parent, 'files')
stl = os.path.join(files_folder, 'cube.stl')
obj = os.path.join(files_folder, 'cube.obj')
a = Stl2Obj()
a.convert(stl, obj)
