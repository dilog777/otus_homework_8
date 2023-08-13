file(GLOB_RECURSE SRC *.h *.hpp *.cpp)

add_executable(bayan ${SRC})

target_link_libraries(bayan PRIVATE
	${Boost_LIBRARIES}
	bayan_lib
)

target_include_directories(bayan PRIVATE
	${Boost_INCLUDE_DIR}
)
