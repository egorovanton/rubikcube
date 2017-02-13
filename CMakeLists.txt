cmake_minimum_required(VERSION 3.6)
project(rubikcube)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp generator/ScrambleGen.h generator/ScrambleGen.cpp)
add_subdirectory(rubikcubetwister)

find_package(Qt5Widgets REQUIRED)

add_executable(rubikcube_gen ${SOURCE_FILES})

target_link_libraries(rubikcube_gen Qt5::Widgets)