#!/bin/bash

rm -rf Build

# Delete CMake Stuff
rm -rf `find . -type d -name CMakeFiles`
rm -rf `find . -type d -name build`
rm -rf `find . -type f -name CMakeCache.txt`
rm -rf `find . -type f -name Makefile`
rm -rf `find . -type f -name cmake_install.cmake`
rm -rf `find . -type f -name CPackConfig.cmake`
rm -rf `find . -type f -name CPackSourceConfig.cmake`

# Delete old libraries
rm -rf `find . -type f -name libGLFW.*`
rm -rf `find . -type f -name libSQLite.*`
rm -rf `find . -type f -name libNordicEngine.*`

