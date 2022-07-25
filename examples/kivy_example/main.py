from kivy.app import App
from kivy.lang.builder import Builder

from stl2obj import Stl2Obj
import os
import pathlib

KV = """
#: import Thread threading.Thread
Button:
    text: 'Run'
    on_release: Thread(target=lambda *args: app.convert()).start()
"""


class TestApp(App):
    def build(self):
        return Builder.load_string(KV)

    def convert(self):
        files_folder = os.path.join(pathlib.Path(__file__).parent.resolve().parents[1], 'files')
        print(f'Files folder {files_folder}')

        stl = os.path.join(files_folder, 'surface.stl')
        obj = os.path.join(files_folder, 'surface.obj')
        a = Stl2Obj()
        a.convert(stl, obj, self.callback)
        print('Conversion done')

    @staticmethod
    def callback(code: int):
        print(code)


TestApp().run()
