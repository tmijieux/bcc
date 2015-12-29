cmake_minimum_required(VERSION 2.8)

project(bcc)
#set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)

# basically this allow the installation folder to be moved anywhere
# and the library to still be found correctly

set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

if (NOT DEFINED CMAKE_ENABLE_C99)
  set(CMAKE_ENABLE_C99 "-std=gnu99")
endif(NOT DEFINED CMAKE_ENABLE_C99)

set(CMAKE_C_FLAGS "${CMAKE_ENABLE_C99} -Wall -Wl,-Xld -Wl,--disable-new-dtags -D_GNU_SOURCE")

enable_testing()

include_directories(.)

add_subdirectory(util)
add_subdirectory(cc1)
add_subdirectory(bcc)


# stackoverflow.com/questions/8934295/
#  add-source-in-a-subdirectory-to-a-cmake-project
# http://www.cmake.org/Wiki/CMake/Editors/Emacs

