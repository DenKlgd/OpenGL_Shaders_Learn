cmake_minimum_required(VERSION 3.8)

project("Shaders")

if (UNIX)
    set(GLFW_DIR "/home/den/glfw-3.3.8")
    set(GLAD_DIR "/home/den/glad")
else()
    set(GLFW_DIR "E:/C++/glfw-3.3.8")
    set(GLAD_DIR "E:/C++/glad")
endif()

find_package(OpenGL REQUIRED)

add_executable(Main "main.cpp" "Shader.h" "Shader.cpp")
add_library(GLAD ${GLAD_DIR}/src/glad.c)

target_include_directories(GLAD PUBLIC ${GLAD_DIR}/include)
target_include_directories(Main PUBLIC ${OPENGL_INCLUDE_DIRS})
target_include_directories(Main PUBLIC ${GLFW_DIR}/include)

target_link_libraries(Main ${OPENGL_LIBRARIES})
target_link_libraries(Main GLAD)

if (UNIX)
    target_link_libraries(Main ${GLFW_DIR}/build/src/libglfw3.a)
    target_link_libraries(Main /lib/x86_64-linux-gnu/libX11.so)
else()
    target_link_libraries(Main ${GLFW_DIR}/src/Debug/glfw3.lib)
endif()
