
project (decode C CXX)
set (SOURCE_FILES
    decode.h
    decode.cpp
)
add_library(decode SHARED STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} isa)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/instruction/isa)

target_link_libraries(${PROJECT_NAME} delay)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/delay)