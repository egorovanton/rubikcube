set(SOURCE_FILES
        solver.cpp solver.h)

find_package(Qt5Widgets REQUIRED)

add_library(lib_solve STATIC ${SOURCE_FILES})
#add_executable(cube_solve main.cpp ${SOURCE_FILES})

target_link_libraries(lib_solve Qt5::Widgets)
#target_link_libraries(cube_solve Qt5::Widgets)
