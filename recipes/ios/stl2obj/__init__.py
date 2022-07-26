from kivy_ios.toolchain import CythonRecipe


class Stl2ObjRecipe(CythonRecipe):
    site_packages_name = 'stl2obj'
    version = 'master'
    url = '/Users/neizvestnyj/PycharmProjects/stl2obj/lib'
    depends = ['python3', 'hostpython3']
    library = f"lib{site_packages_name}.a"

    def install(self):
        self.install_python_package(name=self.so_filename(self.site_packages_name),
                                    is_dir=False
                                    )


recipe = Stl2ObjRecipe()
