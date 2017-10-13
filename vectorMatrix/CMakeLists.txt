cmake_minimum_required(VERSION 3.0)

project(vector_matrix LANGUAGES CXX)

file ( GLOB HEADERS *.h *.hpp)

file ( GLOB SOURCES *.cpp)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


add_subdirectory(tests)
