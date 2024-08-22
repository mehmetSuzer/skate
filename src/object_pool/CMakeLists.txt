
file(GLOB FILES *.cpp *.h)
add_library(object_pool ${FILES})
target_include_directories(object_pool PUBLIC .)
