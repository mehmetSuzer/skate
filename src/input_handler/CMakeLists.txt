
file(GLOB FILES *.cpp *.h)
add_library(input_handler ${FILES})

target_link_libraries(input_handler PUBLIC 
    config 
    camera
)

target_include_directories(input_handler PUBLIC .)
