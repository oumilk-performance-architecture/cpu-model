cmake_minimum_required(VERSION 3.2)
project(arm_cpu)

add_subdirectory(division)
add_subdirectory(core)
set(SOURCE_FILES main.cpp)

add_executable(arm_cpu ${SOURCE_FILES})
target_link_libraries(arm_cpu division)
target_link_libraries(arm_cpu core)

include_directories(core)
install(TARGETS arm_cpu DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})
