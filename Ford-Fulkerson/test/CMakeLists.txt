set(UNIT_TEST_SRC ford_fulkerson_unittest.cpp)
option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

if(ENABLE_UNIT_TESTS)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.8.0
  )
  FetchContent_GetProperties(googletest)
  if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(
      ${googletest_SOURCE_DIR}
      ${googletest_BINARY_DIR}
    )
  endif()

  add_executable(ford_fulkerson_unit_test "")
  target_sources(ford_fulkerson_unit_test
  PRIVATE
    ${UNIT_TEST_SRC} 
  )
  target_include_directories(ford_fulkerson_unit_test
  PUBLIC
    ../include
  )
  target_link_libraries(ford_fulkerson_unit_test
  PRIVATE
    ford_fulkerson 
    gtest_main
  )
  enable_testing()
  message(STATUS "TARGET_FILE is " ${TARGET_FILE})
  add_test(
    NAME google_test
    COMMAND $<TARGET_FILE:ford_fulkerson_unit_test>
  )
endif()
