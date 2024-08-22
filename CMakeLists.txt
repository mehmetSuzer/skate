
cmake_minimum_required(VERSION 3.13.0)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use -O3 for high optimization.
# Use -flto for link-time optimization.
# Use -g0 to disable debug information.
# Use -Wall and -Wextra to enable warnings.
# Comment if any problem occurs or a debug is needed
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -flto -DNDEBUG -g0 -Wall")

project(skate VERSION 0.1.0)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)

file(COPY ${CMAKE_SOURCE_DIR}/glsl DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(lib/stb_image)
add_subdirectory(lib/glad)
add_subdirectory(lib/glm)

add_subdirectory(src/transform)
add_subdirectory(src/material)
add_subdirectory(src/config)
add_subdirectory(src/observer_subject)
add_subdirectory(src/object_pool)
add_subdirectory(src/light)
add_subdirectory(src/camera)
add_subdirectory(src/input_handler)
add_subdirectory(src/vertex)
add_subdirectory(src/texture)
add_subdirectory(src/shader)
add_subdirectory(src/render_state)
add_subdirectory(src/renderable)
add_subdirectory(src/mesh)
add_subdirectory(src/model)
add_subdirectory(src/loadable_model)

add_executable(${PROJECT_NAME} main.cpp scene.h)

target_link_libraries(${PROJECT_NAME} 
    # Source
    loadable_model
    model
    mesh
    renderable
    render_state
    shader
    texture
    input_handler
    camera
    light
    object_pool
    observer_subject
    transform
    
    # Lib
    glm
    glad
    stb_image

    # System
    assimp
    glfw
    OpenGL::GL
)
