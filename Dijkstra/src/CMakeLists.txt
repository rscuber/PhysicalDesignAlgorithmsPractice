set(SRC_LIST dijkstra.cpp)
add_library(dijkstra ${SRC_LIST})
target_include_directories(dijkstra
PUBLIC
  ../include
)
