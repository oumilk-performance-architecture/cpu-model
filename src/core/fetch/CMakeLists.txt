cmake_minimum_required(VERSION 3.2)
project(fetch C CXX)

set(SOURCE_FILES
    fetch.h
    fetch.cpp
)

add_library(fetch SHARED STATIC ${SOURCE_FILES})

install(TARGETS fetch DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES fetch.h DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})
