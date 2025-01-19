cmake_minimum_required(VERSION 3.28)
project(tedit LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(tedit src/main.c)
add_subdirectory(src/)

target_link_libraries(tedit PRIVATE ncurses tinfo)
target_include_directories(tedit PRIVATE include/)

install(TARGETS tedit)
