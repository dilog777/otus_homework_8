file(GLOB_RECURSE SRC *.h *.hpp *.cpp)

add_executable(bayan ${SRC})

target_link_libraries(bayan PRIVATE
	bayan_lib
)
