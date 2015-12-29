

set(
  UTIL_SRC
  list.c
  hash_table.c
  string2.c
  color.c
  stack.c
  error.c
  )

add_library(util STATIC ${UTIL_SRC})
target_link_libraries(util gc)
