set(SRC_LIST kruscal.cpp)
add_library(kruscal ${SRC_LIST})
target_include_directories(kruscal
PUBLIC
  ../include
)
