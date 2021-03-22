cmake_minimum_required(VERSION 3.17)
project(opengltutorial)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(glfw3 3.3 REQUIRED)
add_subdirectory(glad)
add_subdirectory(glm)

add_executable(opengltutorial main.cpp Shader.cpp Shader.h Camera.h Camera.cpp stb_image.h image.cpp)
add_executable(lighttutor light.cpp Shader.cpp Shader.h Camera.cpp Camera.h)

add_dependencies(opengltutorial OpenGL::OpenGL)
add_dependencies(lighttutor OpenGL::OpenGL)
target_link_libraries(opengltutorial OpenGL::OpenGL glfw Glad glm)
target_link_libraries(lighttutor OpenGL::OpenGL glfw Glad glm)
