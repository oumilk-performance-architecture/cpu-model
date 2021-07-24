cmake_minimum_required(VERSION 3.2)
project(core C CXX)

set(SOURCE_FILES core.h core.cpp)
add_library(core SHARED STATIC ${SOURCE_FILES})
install(TARGETS core DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES core.h DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})

add_subdirectory(fetch)
include_directories(fetch)
target_link_libraries(core fetch)

