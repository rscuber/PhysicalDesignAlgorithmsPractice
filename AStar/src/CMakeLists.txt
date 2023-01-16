set(SRC_LIST astar.cpp)
add_library(astar ${SRC_LIST})
target_include_directories(astar
PUBLIC
  ../include
)
