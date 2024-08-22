
file(GLOB FILES *.cpp *.h)
add_library(light ${FILES})

target_link_libraries(light PUBLIC 
    transform 
)

target_include_directories(light PUBLIC .)
