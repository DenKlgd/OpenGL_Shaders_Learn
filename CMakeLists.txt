cmake_minimum_required(VERSION 3.8)

project("Shaders")

# macro(copy_directory src dst)
    # execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${src} ${dst}
        # RESULT_VARIABLE ret
        # OUTPUT_VARIABLE out
        # ERROR_VARIABLE  err
    # )
    # if(ret)
        # message(FATAL_ERROR "ERROR ---> could not be copied: ${err}")
    # endif()
# endmacro()

if (UNIX)
    set(GLFW_DIR "/home/den/glfw-3.3.8")
    set(GLAD_DIR "/home/den/glad")
else()
    set(GLFW_DIR "E:/C++/glfw-3.3.8")
    set(GLAD_DIR "E:/C++/glad")
endif()

set(GLM_DIR "E:/C++/glm-0.9.9.8/glm/cmake/glm")

find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)

add_executable(Main "main.cpp" "Shader.h" "Shader.cpp")
add_library(GLAD ${GLAD_DIR}/src/glad.c)

target_include_directories(GLAD PUBLIC ${GLAD_DIR}/include)
target_include_directories(Main PUBLIC ${OPENGL_INCLUDE_DIRS})
target_include_directories(Main PUBLIC ${GLFW_DIR}/include)
target_include_directories(Main PUBLIC ${GLM_INCLUDE_DIRS})

target_link_libraries(Main ${OPENGL_LIBRARIES})
target_link_libraries(Main GLAD)

if (UNIX)
    target_link_libraries(Main ${GLFW_DIR}/build/src/libglfw3.a)
    target_link_libraries(Main /lib/x86_64-linux-gnu/libX11.so)
else()
    target_link_libraries(Main ${GLFW_DIR}/src/Debug/glfw3.lib)
endif()

#copy_directory("Shaders" "build/Debug")
