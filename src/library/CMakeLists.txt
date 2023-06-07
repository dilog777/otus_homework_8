file(GLOB_RECURSE SRC *.h *.hpp *.cpp)

add_library(helloworld_lib ${SRC})

target_include_directories(helloworld_lib PRIVATE
	"${CMAKE_CURRENT_BINARY_DIR}"
)

configure_file(version.h.in version.h)
