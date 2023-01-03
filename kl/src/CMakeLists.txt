set(SRC_LIST kl.cpp)
add_library(kl ${SRC_LIST})
target_include_directories(kl
PUBLIC
  ../include
)
