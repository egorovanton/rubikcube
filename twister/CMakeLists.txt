
set(SOURCE_FILES
        cube.h cube.cpp
        direction.h direction.cpp
        utils.h utils.cpp)

find_package(Qt5Widgets REQUIRED)


add_library(lib_twist STATIC ${SOURCE_FILES})
add_executable(cube_twist main.cpp ${SOURCE_FILES})

target_link_libraries(lib_twist Qt5::Widgets)
target_link_libraries(cube_twist Qt5::Widgets)

