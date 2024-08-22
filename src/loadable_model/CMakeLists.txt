
file(GLOB FILES *.cpp *.h)
add_library(loadable_model ${FILES})

target_link_libraries(loadable_model PUBLIC 
    renderable
    mesh
)

target_include_directories(loadable_model PUBLIC .)
