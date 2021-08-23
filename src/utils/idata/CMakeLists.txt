project(idata C CXX)

set(SOURCE_FILES idata.h idata.cpp)
add_library(${PROJECT_NAME} SHARED STATIC ${SOURCE_FILES})

#install(TARGETS idata DESTINATION ${CPU_INSTALL_LIB_DIR})
#install(FILES idata.h DESTINATION ${CPU_INSTALL_INCLUDE_DIR})