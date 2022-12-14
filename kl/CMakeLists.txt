CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
PROJECT(KL)
ADD_SUBDIRECTORY(src bin) # 添加函数实现，函数实现中需要CMakeLists说明函数如何编译
ADD_SUBDIRECTORY(test) #测试代码目录，如何测试在次目录下说明
MESSAGE(STATUS "The project binary directory is " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "The project source directory is " ${PROJECT_SOURCE_DIR})

enable_testing() # 开启单元测试，make test
