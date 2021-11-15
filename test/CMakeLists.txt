cmake_minimum_required(VERSION 3.2)
project(arm_tests)

add_subdirectory(lib/googletest)

include_directories(${CPU_HEADERS_DIR})
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} gtest)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

