cmake_minimum_required(VERSION 3.12)
project(week7 C)

set(CMAKE_C_STANDARD 99)

add_executable(week7 ex5.c)
target_link_libraries(week7 pthread)