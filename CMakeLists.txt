
cmake_minimum_required(VERSION 3.12.0)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Comment if any problem occurs or a debug is needed
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

project(opengl VERSION 0.1.0)

find_package(OpenGL REQUIRED)

set(SRC_DIR src)
set(DATA_DIR data)
set(GLSL_DIR glsl)

file(COPY ${CMAKE_SOURCE_DIR}/${GLSL_DIR} DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/${DATA_DIR} DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(${SRC_DIR}/config)
include_directories(${SRC_DIR}/config)

add_subdirectory(${SRC_DIR}/exception)
include_directories(${SRC_DIR}/exception)

add_subdirectory(${SRC_DIR}/observer_subject)
include_directories(${SRC_DIR}/observer_subject)

add_subdirectory(${SRC_DIR}/object_pool)
include_directories(${SRC_DIR}/object_pool)

add_subdirectory(${SRC_DIR}/stb)
include_directories(${SRC_DIR}/stb)

add_subdirectory(${SRC_DIR}/glad)
include_directories(${SRC_DIR}/glad)

add_subdirectory(${SRC_DIR}/glm)
include_directories(${SRC_DIR}/glm)

add_subdirectory(${SRC_DIR}/light)
include_directories(${SRC_DIR}/light)

add_subdirectory(${SRC_DIR}/material)
include_directories(${SRC_DIR}/material)

add_subdirectory(${SRC_DIR}/util)
include_directories(${SRC_DIR}/util)

add_subdirectory(${SRC_DIR}/camera)
include_directories(${SRC_DIR}/camera)

add_subdirectory(${SRC_DIR}/input_handler)
include_directories(${SRC_DIR}/input_handler)

add_subdirectory(${SRC_DIR}/vertex)
include_directories(${SRC_DIR}/vertex)

add_subdirectory(${SRC_DIR}/texture)
include_directories(${SRC_DIR}/texture)

add_subdirectory(${SRC_DIR}/shader)
include_directories(${SRC_DIR}/shader)

add_subdirectory(${SRC_DIR}/mesh)
include_directories(${SRC_DIR}/mesh)

add_subdirectory(${SRC_DIR}/model)
include_directories(${SRC_DIR}/model)

add_subdirectory(${SRC_DIR}/assimp_model)
include_directories(${SRC_DIR}/assimp_model)

add_subdirectory(${SRC_DIR}/scene)
include_directories(${SRC_DIR}/scene)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} 
    assimp_model
    mesh
    shader
    texture
    input_handler
    camera
    util
    light
    glm
    glad
    stb
    object_pool
    observer_subject
    exception
    assimp
    glfw
    OpenGL::GL
)
