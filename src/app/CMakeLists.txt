file(GLOB_RECURSE SRC *.h *.hpp *.cpp)

add_executable(helloworld ${SRC})

target_link_libraries(helloworld PRIVATE
	helloworld_lib
)
