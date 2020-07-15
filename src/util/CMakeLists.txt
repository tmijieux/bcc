

set(UTIL_SRC
  alloc.c alloc.h
  color.c color.h
  error.c error.h
  hash_table.c hash_table.h
  list.c list.h list_node.h
  stack.c stack.h
  string2.c string2.h
  )

add_library(util STATIC ${UTIL_SRC})
target_link_libraries(util gc)

get_filename_component(CMAKE_CURRENT_PARENT_DIR
  ../ ABSOLUTE
  BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(util INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_PARENT_DIR}>
  )
