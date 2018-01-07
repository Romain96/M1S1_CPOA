cmake_minimum_required(VERSION 3.0)
project(Projet_Particules LANGUAGES C CXX)

if(MSVC)
	add_definitions("-D_USE_MATH_DEFINES")
else()
	add_compile_options(-std=c++11 -Wall)
endif()


add_subdirectory(vectorMatrix)
add_subdirectory(image)
add_subdirectory(csg)
add_subdirectory(particle)
add_subdirectory(InterfaceCSG)
