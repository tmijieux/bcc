

set(
  BCC_SRC
  main.c
  chain.c
  option.c
  )

add_executable(bcc ${BCC_SRC})
target_link_libraries(bcc util)
