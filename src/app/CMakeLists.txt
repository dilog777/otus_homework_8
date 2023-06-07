file(GLOB_RECURSE SRC *.h *.hpp *.cpp)

add_executable(helloworld ${SRC})

target_include_directories(helloworld PRIVATE
	../library
)

target_link_libraries(helloworld PRIVATE
	helloworld_lib
)
