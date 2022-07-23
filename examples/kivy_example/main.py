from kivy.app import App
from kivy.lang.builder import Builder

from stl2obj import Stl2Obj
import os
import pathlib

KV = """
Button:
    text: 'Run'
    on_release: app.convert()
"""


class TestApp(App):
    def build(self):
        return Builder.load_string(KV)

    @staticmethod
    def convert():
        files_folder = os.path.join(pathlib.Path(__file__).parent.resolve().parents[1], 'files')
        print(f'Files folder {files_folder}')

        stl = os.path.join(files_folder, 'surface.stl')
        obj = os.path.join(files_folder, 'surface.obj')
        a = Stl2Obj()
        a.convert(stl, obj)


TestApp().run()
