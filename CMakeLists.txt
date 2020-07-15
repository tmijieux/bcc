cmake_minimum_required(VERSION 3.2)
project(bcc C)


# basically this allow the installation folder to be moved anywhere
# and the library to still be found correctly
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

if (NOT DEFINED CMAKE_ENABLE_C99)
  set(CMAKE_ENABLE_C99 "-std=gnu99")
endif(NOT DEFINED CMAKE_ENABLE_C99)

set(CMAKE_C_FLAGS "${CMAKE_ENABLE_C99} -Wall -Wextra -D_GNU_SOURCE")

enable_testing()

add_subdirectory(src)
