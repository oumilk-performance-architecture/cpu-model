project(decoder C CXX)
set(SOURCE_FILES 
    decoder.cpp 
    decoder.h
    isa.h
    )
add_library(decoder SHARED STATIC ${SOURCE_FILES})

add_subdirectory(riscv/rv32i)
target_link_libraries(${PROJECT_NAME} rv32i)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/instruction/isa/riscv/rv32i)

#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uinstr)