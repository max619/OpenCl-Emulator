# CMakeList.txt : CMake project for OpenCl-Emulator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("OpenCl-Emulator")

set(CL_TARGET_VERSION 120)
set(OPENCL_EMULATOR_LIBRARY_NAME "opencl-emulator")

add_subdirectory(3rdParty)
add_subdirectory(src)
