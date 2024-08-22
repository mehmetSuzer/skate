
file(GLOB FILES *.cpp *.h)
add_library(render_state ${FILES})

target_link_libraries(render_state PUBLIC 
    config 
    shader
)

target_include_directories(render_state PUBLIC .)
