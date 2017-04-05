cmake_minimum_required(VERSION 3.0)

enable_testing()

# Make sure that we're compiling C++14 source code.
set(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(LZW lzw435.cpp)
add_executable(LZWM lzw435M.cpp)
#add_executable(test-vector-binary vector-binary.cpp)
#add_executable(test-vector-sort vector-sort.cpp)

macro(add_printout)
  add_custom_target(printout
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND a2ps -Afill -o- ${ARGN} | ps2pdf - ${CMAKE_BINARY_DIR}/printout.pdf)
endmacro()

add_printout(lzw435.cpp, lzw435M.cpp Readme.txt)
