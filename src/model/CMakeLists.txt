
file(GLOB FILES *.cpp *.h)
add_library(model INTERFACE)

target_link_libraries(model INTERFACE 
    renderable
    mesh
)

target_include_directories(model INTERFACE .)
