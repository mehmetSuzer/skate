
cmake_minimum_required(VERSION 3.0.0)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Comment if any problem occurs or a debug is needed
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")

project(opengl VERSION 0.1.0)

find_package(OpenGL REQUIRED)

set(LIB_DIR lib)
set(DATA_DIR data)
set(GLSL_DIR glsl)

file(COPY ${CMAKE_SOURCE_DIR}/${GLSL_DIR} DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/${DATA_DIR} DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(${LIB_DIR}/config)
include_directories(${LIB_DIR}/config)

add_subdirectory(${LIB_DIR}/exception)
include_directories(${LIB_DIR}/exception)

add_subdirectory(${LIB_DIR}/observer_subject)
include_directories(${LIB_DIR}/observer_subject)

add_subdirectory(${LIB_DIR}/object_pool)
include_directories(${LIB_DIR}/object_pool)

add_subdirectory(${LIB_DIR}/stb)
include_directories(${LIB_DIR}/stb)

add_subdirectory(${LIB_DIR}/json)
include_directories(${LIB_DIR}/json)

add_subdirectory(${LIB_DIR}/glad)
include_directories(${LIB_DIR}/glad)

add_subdirectory(${LIB_DIR}/glm)
include_directories(${LIB_DIR}/glm)

add_subdirectory(${LIB_DIR}/light)
include_directories(${LIB_DIR}/light)

add_subdirectory(${LIB_DIR}/material)
include_directories(${LIB_DIR}/material)

add_subdirectory(${LIB_DIR}/common)
include_directories(${LIB_DIR}/common)

add_subdirectory(${LIB_DIR}/camera)
include_directories(${LIB_DIR}/camera)

add_subdirectory(${LIB_DIR}/input_handler)
include_directories(${LIB_DIR}/input_handler)

add_subdirectory(${LIB_DIR}/vertex)
include_directories(${LIB_DIR}/vertex)

add_subdirectory(${LIB_DIR}/vbo)
include_directories(${LIB_DIR}/vbo)

add_subdirectory(${LIB_DIR}/ebo)
include_directories(${LIB_DIR}/ebo)

add_subdirectory(${LIB_DIR}/vao)
include_directories(${LIB_DIR}/vao)

add_subdirectory(${LIB_DIR}/texture)
include_directories(${LIB_DIR}/texture)

add_subdirectory(${LIB_DIR}/shader)
include_directories(${LIB_DIR}/shader)

add_subdirectory(${LIB_DIR}/mesh)
include_directories(${LIB_DIR}/mesh)

add_subdirectory(${LIB_DIR}/model)
include_directories(${LIB_DIR}/model)

add_subdirectory(${LIB_DIR}/scene)
include_directories(${LIB_DIR}/scene)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME} 
    mesh
    shader
    texture
    vao
    ebo
    vbo
    input_handler
    camera
    common
    light
    glm
    glad
    stb
    object_pool
    observer_subject
    exception
    glfw
    OpenGL::GL
)
