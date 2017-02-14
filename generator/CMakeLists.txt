
set(SOURCE_FILES
        ScrambleGen.h ScrambleGen.cpp)

find_package(Qt5Widgets REQUIRED)

add_library(lib_gen STATIC ${SOURCE_FILES})
#add_executable(cube_gen main.cpp ${SOURCE_FILES})

target_link_libraries(lib_gen Qt5::Widgets)
#target_link_libraries(cube_gen Qt5::Widgets)
