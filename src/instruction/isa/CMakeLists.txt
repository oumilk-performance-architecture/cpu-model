project(isa C CXX)


set(SOURCE_FILES isa.cpp isa.h)
add_library(isa SHARED STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} armv6m)
add_subdirectory(armv6m)
target_include_directories(${PROJECT_NAME} PUBLIC armv6m)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uinstr)
#install(TARGETS isa DESTINATION ${CPU_INSTALL_LIB_DIR})
#install(FILES isa.h DESTINATION ${CPU_INSTALL_INCLUDE_DIR})