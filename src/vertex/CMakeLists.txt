
add_library(vertex INTERFACE)

target_link_libraries(vertex INTERFACE 
    config
    glm
)

target_include_directories(vertex INTERFACE .)
