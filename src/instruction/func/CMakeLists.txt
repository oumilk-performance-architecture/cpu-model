project(func C CXX)

set(SOURCE_FILES func.h func.cpp)
add_library(func SHARED STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uinstr)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uop)
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uop)
#install(TARGETS func DESTINATION ${CPU_INSTALL_LIB_DIR})
#install(FILES func.h DESTINATION ${CPU_INSTALL_INCLUDE_DIR})
