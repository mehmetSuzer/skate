
file(GLOB FILES *.c *.h)
add_library(glad ${FILES})
target_include_directories(glad PUBLIC .)
