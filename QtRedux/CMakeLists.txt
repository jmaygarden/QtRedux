cmake_minimum_required(VERSION 3.8.0)

project(QtRedux)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_definitions(-DQTREDUX_LIBRARY)

file(GLOB QtRedux_HEADERS *.h)
file(GLOB QtRedux_SOURCES *.cpp)

add_library(QtRedux SHARED ${QtRedux_HEADERS} ${QtRedux_SOURCES})

target_link_libraries(QtRedux Qt5::Core)

