project(rv32i C CXX)

set(SOURCE_FILES
rv32i.h
rv32i.cpp
../../isa.h
)

add_library(rv32i SHARED STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} uinstr)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uinstr)

target_link_libraries(${PROJECT_NAME} uop)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uop)