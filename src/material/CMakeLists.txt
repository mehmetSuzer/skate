
add_library(material INTERFACE)

target_link_libraries(material INTERFACE 
    glm
)

target_include_directories(material INTERFACE .)
