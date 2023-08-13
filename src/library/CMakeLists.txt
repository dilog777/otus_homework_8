file(GLOB_RECURSE SRC *.h *.hpp *.cpp)

add_library(bayan_lib ${SRC})

target_include_directories(bayan_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(bayan_lib PRIVATE
	${Boost_INCLUDE_DIR}
)

target_link_libraries(bayan_lib PRIVATE
	${Boost_LIBRARIES}
)
