cmake_minimum_required(VERSION 3.6)
project(rubikcube)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(twister)
add_subdirectory(generator)
#set(SOURCE_FILES )

find_package(Qt5Widgets REQUIRED)

add_executable(cube_all main.cpp ${SOURCE_FILES})

target_link_libraries(cube_all lib_gen lib_twist Qt5::Widgets)