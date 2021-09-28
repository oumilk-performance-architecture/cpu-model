project(bus C CXX)

set(SOURCE_FILES bus.h bus.cpp)

add_library(bus SHARED STATIC ${SOURCE_FILES})
#install(TARGETS bus DESTINATION ${CPU_INSTALL_LIB_DIR})
#install(FILES bus.h DESTINATION ${CPU_INSTALL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} delay)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/delay)

target_link_libraries(${PROJECT_NAME} fetch)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/core/fetch)



