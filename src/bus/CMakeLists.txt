project(bus C CXX)

set(SOURCE_FILES bus.h bus.cpp)

add_library(bus SHARED STATIC ${SOURCE_FILES})
#install(TARGETS bus DESTINATION ${CPU_INSTALL_LIB_DIR})
#install(FILES bus.h DESTINATION ${CPU_INSTALL_INCLUDE_DIR})


