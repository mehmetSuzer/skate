
file(GLOB FILES *.cpp *.h)
add_library(camera ${FILES})

target_link_libraries(camera PUBLIC 
    transform 
)

target_include_directories(camera PUBLIC .)
