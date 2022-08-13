cmake_minimum_required (VERSION 3.8)

project ("stl2obj")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCES "stl2obj/src/*" "stl2obj/src/obj_to_stl/*" "stl2obj/src/stl_to_obj/*")

add_executable(stl2obj ${SOURCES})
