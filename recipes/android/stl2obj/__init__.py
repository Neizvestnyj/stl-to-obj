from pythonforandroid.recipe import CythonRecipe

'''
don't use `install_in_hostpython = True` because it provokes an `setuptools` error
`import _distutils_hack.override # noqa: f401`
'''


class Stl2ObjRecipe(CythonRecipe):
    version = 'master'
    name = 'stl2obj'
    url = f"https://github.com/Neizvestnyj/stl-to-obj/archive/{version}.zip"

    depends = ['setuptools', 'cython']

    def get_recipe_env(self, arch):
        env = super().get_recipe_env(arch)
        env['LDFLAGS'] += ' -lc++_shared'
        return env


recipe = Stl2ObjRecipe()
