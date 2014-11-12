cmake_minimum_required(VERSION 2.8)
project(ConstList)

set(
	CMAKE_CXX_FLAGS
	"-std=c++14 -W -Wall -Wextra -Winline -pedantic"
)

include_directories(
	src/
)

add_executable(
	tests
	test.cc
)

target_link_libraries(
	tests
	gtest
)

add_custom_command(
	TARGET tests
	POST_BUILD COMMAND ./tests
)
