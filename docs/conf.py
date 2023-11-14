import os, subprocess

project = 'Errors C++'
copyright = '2023, Alfi Maulana'
author = 'Alfi Maulana'

extensions = ['breathe']

subprocess.call('cmake .. -B ../build -D BUILD_DOCS=ON', shell=True)
subprocess.call('cmake --build ../build --target docs', shell=True)

breathe_projects = {"errors": "../build/docs"}
breathe_default_project = "errors"

html_theme = 'furo'
html_static_path = ['_static']
