cmake_minimum_required(VERSION 3.17)
project(Glad)

add_library(Glad include/glad/glad.h src/glad.c)
target_link_libraries(Glad dl)
target_include_directories(Glad PUBLIC include/)