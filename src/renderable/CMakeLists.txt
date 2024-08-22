
file(GLOB FILES *.cpp *.h)
add_library(renderable ${FILES})

target_link_libraries(renderable PUBLIC 
    transform
    shader
)

target_include_directories(renderable PUBLIC .)
