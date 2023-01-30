set(SRC_LIST ford_fulkerson.cpp)
add_library(ford_fulkerson ${SRC_LIST})
target_include_directories(ford_fulkerson
PUBLIC
  ../include
)
