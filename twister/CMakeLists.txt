
set(SOURCE_FILES
        utils.h utils.cpp
        cube.h cube.cpp
        direction.h direction.cpp
        mask.h mask.cpp
        )

find_package(Qt5Widgets REQUIRED)


add_library(lib_twist STATIC ${SOURCE_FILES})
target_link_libraries(lib_twist Qt5::Widgets)

add_executable(cube_twist main.cpp ${SOURCE_FILES})
target_link_libraries(cube_twist Qt5::Widgets)

