import os
import sys
sys.path.append('config/utils')
import File
import Args
import Conan
import Cmake
import Compiler

#Conan.setup()

make = Args.has('--make')

print(make)

build_folder = 'make' if make else 'build'

File.rm(build_folder)
File.mkdir(build_folder)
File.cd(build_folder)

Conan.run(Compiler.clang)
Cmake.run(Cmake.make)

File.chown('.')
