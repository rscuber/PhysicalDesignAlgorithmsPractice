set(SRC_LIST fm.cpp)
add_library(fm ${SRC_LIST})
target_include_directories(fm
PUBLIC
  ../include
)
