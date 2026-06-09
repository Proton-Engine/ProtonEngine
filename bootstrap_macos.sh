#!/bin/bash

mkdir build
python3 -m venv build/proton-engine-python-venv
source build/proton-engine-python-venv/bin/activate
python3 -m pip install jinja2

conan install -pr:a=clang-20-macos-armv8 -s compiler.cppstd=23 -s build_type=RelWithDebInfo -c tools.cmake.cmaketoolchain:generator="Ninja" . --build=missing
conan install -pr:a=clang-20-macos-armv8 -s compiler.cppstd=23 -s build_type=Debug -c tools.cmake.cmaketoolchain:generator="Ninja" . --build=missing
