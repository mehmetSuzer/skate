
file(GLOB FILES *.cpp *.h)
add_library(config INTERFACE)

target_link_libraries(config INTERFACE 
    glad
)

target_include_directories(config INTERFACE .)
