import os, subprocess

project = 'cpp'
copyright = '2023, Alfi Maulana'
author = 'Alfi Maulana'

extensions = ['breathe']

subprocess.call('cmake ../error -B ../error/build -D BUILD_DOCS=ON', shell=True)
subprocess.call('cmake --build ../error/build --target docs', shell=True)

breathe_projects = {"error": "../error/build/docs"}
breathe_default_project = "error"

html_theme = 'furo'
html_static_path = ['_static']
