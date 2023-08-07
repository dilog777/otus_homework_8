file(GLOB_RECURSE SRC *.h *.hpp *.cpp)

add_executable(bayan_test ${SRC})

target_link_libraries(bayan_test PRIVATE
	${Boost_LIBRARIES}
	bayan_lib
)

target_include_directories(bayan_test PRIVATE
	${Boost_INCLUDE_DIR}
)

set_target_properties(bayan_test PROPERTIES
	COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)

add_test(bayan_test bayan_test)
