from kivy.app import App
from kivy.lang.builder import Builder
from kivy.uix.modalview import ModalView
from kivy.logger import Logger

from render import Renderer

from stl2obj import Stl2Obj
import pathlib
import os

KV = """
#: import Thread threading.Thread
BoxLayout:
    ScrollView:
        BoxLayout:
            id: box
            orientation: 'vertical'
            size_hint_y: None
            height: self.minimum_height
            spacing: dp(20)
            padding: dp(5), dp(20), dp(5), dp(20)
            
            TextInput:
                id: field_stl
                text: 'Dolphin.stl'
                size_hint_y: None
                height: self.minimum_height
                
            TextInput:
                id: field_obj
                text: 'Dolphin.obj'
                size_hint_y: None
                height: self.minimum_height
            
            Widget:
                size_hint_y: None
                height: max(root.height - dp(100) - field_obj.height * 2 - dp(20 * 4) - dp(20 * 2), dp(10))
                
            Button:
                id: run
                text: 'Run'
                size_hint_y: None
                height: dp(50)
                on_release: Thread(target=lambda *args: app.convert()).start()
                
            Button:
                text: 'Preview'
                size_hint_y: None
                height: dp(50)
                on_release: app.preview()
"""


class TestApp(App):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.render = None
        self.view = None

    def build(self):
        return Builder.load_string(KV)

    @staticmethod
    def get_file(file: str):
        files_folder = os.path.join(pathlib.Path(__file__).parent.resolve(), 'files')
        return os.path.join(files_folder, file)

    def convert(self):
        self.root.ids.run.disabled = True
        stl = self.get_file(self.root.ids.field_stl.text)
        obj = self.get_file(self.root.ids.field_obj.text)

        Stl2Obj().convert(stl, obj, self.callback)
        print('Conversion done')

    def callback(self, code: int):
        self.root.ids.run.disabled = False
        print(code)

    def preview(self):
        try:
            if not self.render:
                print(self.root.ids.obj)
                obj = self.get_file(self.root.ids.field_obj.text)
                self.render = Renderer(source=obj)
                self.view = ModalView(size_hint=(0.8, 0.8))
                self.view.add_widget(self.render)

            self.view.open()
        except OverflowError as e:
            # https://github.com/kivy/kivy/issues/7105#issuecomment-1195393114
            Logger.critical(msg=f'{e}')


TestApp().run()