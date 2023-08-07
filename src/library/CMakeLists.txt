file(GLOB_RECURSE SRC *.h *.hpp *.cpp)

add_library(bayan_lib ${SRC})

target_include_directories(bayan_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(bayan_lib PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

configure_file(version.h.in version.h)
