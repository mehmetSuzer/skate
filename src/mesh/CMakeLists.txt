
file(GLOB FILES *.cpp *.h)
add_library(mesh ${FILES})

target_link_libraries(mesh PUBLIC 
    vertex
    render_state
    texture
    material
)

target_include_directories(mesh PUBLIC .)
