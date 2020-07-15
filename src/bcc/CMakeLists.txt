

set(BCC_SRC
  main.c
  chain.c
  chain.h
  option.c
  option.h
  )

add_executable(bcc ${BCC_SRC})
target_link_libraries(bcc util)

