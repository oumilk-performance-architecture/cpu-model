cmake_minimum_required(VERSION 3.21)

project(riscv_cpu VERSION 0.1)
configure_file(ProjectConfig.h.in ProjectConfig.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(CPU_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CPU_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(CPU_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(CPU_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories(${CPU_INSTALL_INCLUDE_DIR})
include_directories(${CPU_HEADERS_DIR})

add_subdirectory(src)
#add_subdirectory(test)

target_include_directories(riscv_cpu PUBLIC "${PROJECT_BINARY_DIR}")
