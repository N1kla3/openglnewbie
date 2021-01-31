cmake_minimum_required(VERSION 3.17)
project(opengltutorial)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(glfw3 3.3 REQUIRED)
add_subdirectory(glad)
add_subdirectory(glm-0.9.9.8)

add_executable(opengltutorial main.cpp Shader.cpp Shader.h stb_image.h image.cpp)

add_dependencies(opengltutorial OpenGL::OpenGL)
target_link_libraries(opengltutorial OpenGL::OpenGL glfw Glad glm)
