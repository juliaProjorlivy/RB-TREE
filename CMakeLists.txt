cmake_minimum_required(VERSION 3.28)
project(RBtree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(RBtree INTERFACE)
target_include_directories(RBtree INTERFACE rbtree)

add_subdirectory(src)

option(TEST_BUILD "" ON)
if(TEST_BUILD)
message(STATUS "Building test...")
add_subdirectory(tests)
endif()

