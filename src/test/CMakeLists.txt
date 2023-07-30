file(GLOB_RECURSE SRC *.h *.hpp *.cpp)

add_executable(test_google ${SRC})

target_link_libraries(test_google PRIVATE
	GTest::gtest_main
	helloworld_lib
)

include(GoogleTest)
gtest_discover_tests(test_google)
