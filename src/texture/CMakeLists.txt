
file(GLOB FILES *.cpp *.h)
add_library(texture ${FILES})

target_link_libraries(texture PUBLIC 
    config 
    stb_image
)

target_include_directories(texture PUBLIC .)
