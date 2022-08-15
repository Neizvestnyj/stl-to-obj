"""""""""""""""""
Usage
"""""""""""""""""

Stl2Obj - root class
--------------------

**Base convert files example**

.. code-block:: python

    from stl2obj import Stl2Obj

    src = 'path-to-src-file'  # .stl or .obj
    dst = 'path-to-dst-file'  # .stl or .obj

    Stl2Obj().convert(src, dst)

:code:`convert` function takes:

- src - :code:`str` path to `.stl` or `.obj` file
- dst - :code:`str` path to output `.obj` or `.stl` file
- debug - :code:`bool` disable **c++** `cout`
- callback - :code:`object` callback function in python, default :code:`None`
- progress_callback - :code:`object` called when part of the file processing has been completed, it is always 1, so do in your project

.. code-block:: python

    def progress_callback(self, value: int):
        self.total_progress += value

:code:`stl_mode_converter` function takes:

- src - :code:`str` path to `.stl` file
- dst - :code:`str` path to output `.stl` file
- mode - :code:`str` **ASCII**, **BIN** or **AUTO**
- callback - :code:`object` callback function in python, default :code:`None`
- progress_callback - :code:`object` like in :code:`convert` function
