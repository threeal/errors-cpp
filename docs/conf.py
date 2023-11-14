import os, subprocess

project = 'Errors C++'
copyright = '2023, Alfi Maulana'
author = 'Alfi Maulana'

extensions = ['breathe']

subprocess.call('cmake .. -B ../build -D BUILD_DOCS=ON', shell=True)
subprocess.call('cmake --build ../build --target docs', shell=True)

breathe_projects = {"error": "../build/docs"}
breathe_default_project = "error"

html_theme = 'furo'
html_static_path = ['_static']
