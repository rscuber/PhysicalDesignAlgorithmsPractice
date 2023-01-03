set(SRC_LIST prim.cpp)
add_library(prim ${SRC_LIST})
target_include_directories(prim
PUBLIC
  ../include
)
