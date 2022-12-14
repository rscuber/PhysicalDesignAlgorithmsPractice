# not complete
CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
enable_testing()
SET(GTEST_INCLUDE_DIR ../google_test/include/gtest)
find_package(GTest REQUIRED)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIR})
SET(kl_unit_test, )
ADD_EXECUTABLE(${kl_unit_test} kl_unittest.cpp)
