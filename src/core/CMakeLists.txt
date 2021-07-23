cmake_minimum_required(VERSION 3.2)
project(core C CXX)

#add_subdirectory(fetch)
set(SOURCE_FILES core.h core.cpp)

add_library(core SHARED STATIC ${SOURCE_FILES})

install(TARGETS core DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES core.h DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})
