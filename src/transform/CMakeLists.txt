
file(GLOB FILES *.cpp *.h)
add_library(transform ${FILES})

target_link_libraries(transform PUBLIC 
    glm 
)

target_include_directories(transform PUBLIC .)
