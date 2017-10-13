cmake_minimum_required(VERSION 3.0)

project(InterfaceCSG LANGUAGES C CXX)

find_package(OpenGL REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

file ( GLOB HEADERS *.h)
file ( GLOB SOURCES *.cpp)

add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../vectorMatrix
	${CMAKE_CURRENT_SOURCE_DIR}/../image
	${CMAKE_CURRENT_SOURCE_DIR}/../csg
	${CMAKE_CURRENT_SOURCE_DIR}/../particle)


target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::OpenGL ${OPENGL_LIBRARIES})

#target_link_libraries(${PROJECT_NAME} csg vector_matrix image particle Qt5::Widgets Qt5::OpenGL ${OPENGL_LIBRARIES})
