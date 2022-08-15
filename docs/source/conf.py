import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath("."))))

project = 'stl2obj'
copyright = '2022, Neizvestnyj'
author = 'Neizvestnyj'

version = '0.3'
release = version

extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.napoleon',
    'sphinx.ext.autosectionlabel',
    'sphinx.ext.intersphinx',
]

templates_path = ['_templates']

exclude_patterns = []

html_theme = 'sphinx_rtd_theme'
html_theme_options = {
    "canonical_url": "https://stl-to-obj.readthedocs.io/en/latest/",
    "navigation_depth": 2,
    "collapse_navigation": False,
    "titles_only": True,
}

html_static_path = ['_static']
html_favicon = "_static/logo.png"
html_logo = "_static/logo.png"
