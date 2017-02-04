cmake_minimum_required(VERSION 3.6)
project(rubikcube)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp ScrambleGen.cpp ScrambleGen.h)
find_package(Qt5Widgets REQUIRED)

add_executable(rubikcube ${SOURCE_FILES})

target_link_libraries(rubikcube Qt5::Widgets)