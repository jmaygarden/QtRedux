cmake_minimum_required(VERSION 3.8.0)

project(todos)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

file(GLOB todos_HEADERS *.h)
file(GLOB todos_SOURCES *.cpp)

add_executable(todos WIN32 ${todos_HEADERS} ${todos_SOURCES})

target_include_directories(todos PUBLIC ../../QtRedux)

target_link_libraries(todos Qt5::Core Qt5::Widgets QtRedux)

