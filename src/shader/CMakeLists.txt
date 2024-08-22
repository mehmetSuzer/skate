
file(GLOB FILES *.cpp *.h)
add_library(shader ${FILES})

target_link_libraries(shader PUBLIC 
    config 
    light
)

target_include_directories(shader PUBLIC .)
