from kivy.clock import Clock
from kivy.uix.widget import Widget
from kivy.properties import StringProperty
from kivy.graphics.transformation import Matrix
from kivy.graphics.opengl import glEnable, glDisable, GL_DEPTH_TEST
from kivy.graphics import RenderContext, Callback, PushMatrix, PopMatrix, \
    Color, Translate, Rotate, Mesh, UpdateNormalMatrix
from objloader import ObjFile

import pathlib
import os


class Renderer(Widget):
    source = StringProperty()

    def __init__(self, **kwargs):
        super(Renderer, self).__init__(**kwargs)
        if self.source:
            self.canvas = RenderContext(compute_normal_mat=True)
            folder = pathlib.Path(__file__).parent.resolve()
            self.canvas.shader.source = os.path.join(folder, 'simple.glsl')

            self.scene = ObjFile(self.source)

            with self.canvas:
                self.cb = Callback(self.setup_gl_context)
                PushMatrix()
                self.setup_scene()
                PopMatrix()
                self.cb = Callback(self.reset_gl_context)

            Clock.schedule_interval(self.update_glsl, 1 / 60.)
        else:
            pass

    @staticmethod
    def _prepare_file(filename: str):
        """
        :param filename:
        :return:
        If f contains only one /
        """

        with open(filename) as opened_file:
            lines = [line.replace('/', '//') if '//' not in line else line for line in opened_file]
            print(lines)

        with open(filename, 'w') as new_file:
            new_file.write(''.join(lines))

    @staticmethod
    def setup_gl_context(*args):
        glEnable(GL_DEPTH_TEST)

    @staticmethod
    def reset_gl_context(*args):
        glDisable(GL_DEPTH_TEST)

    def update_glsl(self, delta):
        asp = self.width / float(self.height)
        proj = Matrix().view_clip(-asp, asp, -1, 1, 1, 100, 1)
        self.canvas['projection_mat'] = proj
        self.canvas['diffuse_light'] = (1.0, 1.0, 0.8)
        self.canvas['ambient_light'] = (0.1, 0.1, 0.1)
        self.rot.angle += delta * 100

    def setup_scene(self):
        Color(1, 1, 1, 1)
        PushMatrix()
        Translate(0, 0, -3)
        self.rot = Rotate(1, 1, 1, 0)
        m = list(self.scene.objects.values())[0]
        UpdateNormalMatrix()
        self.mesh = Mesh(
            vertices=m.vertices,
            indices=m.indices,
            fmt=m.vertex_format,
            mode='triangles',
        )
        PopMatrix()
