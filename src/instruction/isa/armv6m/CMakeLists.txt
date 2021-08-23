project(armv6m C CXX)

set(SOURCE_FILES
armv6m.h
armv6m.cpp
)

add_library(armv6m SHARED STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} uinstr)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uinstr)
#install(TARGETS armv6m DESTINATION ${CPU_INSTALL_LIB_DIR})
#install(FILES armv6m.h DESTINATION ${CPU_INSTALL_INCLUDE_DIR})