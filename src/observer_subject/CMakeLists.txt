
file(GLOB FILES *.cpp *.h)
add_library(observer_subject ${FILES})

target_link_libraries(observer_subject PUBLIC 
    config 
)

target_include_directories(observer_subject PUBLIC .)
