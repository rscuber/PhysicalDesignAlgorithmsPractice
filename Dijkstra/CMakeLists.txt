cmake_minimum_required(VERSION 3.21)
project(Dijkstra LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src) # 添加函数实现，函数实现中需要CMakeLists说明函数如何编译

message(STATUS "The project binary directory is " ${PROJECT_BINARY_DIR})
message(STATUS "The project source directory is " ${PROJECT_SOURCE_DIR})

#Unit Test
add_subdirectory(test) #测试代码目录，如何测试在次目录下说明
message(STATUS "The gtest source directory is " ${gtest_SOURCE_DIR})
