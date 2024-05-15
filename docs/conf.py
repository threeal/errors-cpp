import os, subprocess

project = 'Errors C++'
author = 'Alfi Maulana'
copyright = '2023-2024, Alfi Maulana'
version = '1.0.0'
release = '1.0.0'

extensions = ['breathe']

subprocess.call('cmake .. -B ../build -D BUILD_DOCS=ON', shell=True)
subprocess.call('cmake --build ../build --target errors_docs', shell=True)

breathe_projects = {
    "errors": "../build/errors_docs",
}

html_theme = 'furo'
html_static_path = ['_static']
