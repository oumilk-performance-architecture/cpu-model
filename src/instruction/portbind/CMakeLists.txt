project(portbind C CXX)

set(SOURCE_FILES
portbind.h
portbind.cpp
)

add_library(portbind SHARED STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} uinstr)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uinstr)

target_link_libraries(${PROJECT_NAME} uop)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uop)
#install(TARGETS armv6m DESTINATION ${CPU_INSTALL_LIB_DIR})
#install(FILES armv6m.h DESTINATION ${CPU_INSTALL_INCLUDE_DIR})