
set(SOURCE_FILES
        main.cpp
        cube.h cube.cpp
        direction.h direction.cpp
        utils.h utils.cpp)

find_package(Qt5Widgets REQUIRED)

add_executable(rubikcube_twist ${SOURCE_FILES})

target_link_libraries(rubikcube_twist Qt5::Widgets)
