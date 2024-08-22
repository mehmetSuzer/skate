
file(GLOB FILES *.cpp *.h)
add_library(stb_image ${FILES})
target_include_directories(stb_image PUBLIC .)
