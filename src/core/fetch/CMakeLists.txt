project(fetch C CXX)

set(SOURCE_FILES
    fetch.h
    fetch.cpp
)

add_library(fetch SHARED STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} idata)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/idata)

target_link_libraries(${PROJECT_NAME} delay)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/delay)

target_link_libraries(${PROJECT_NAME} bus)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/bus)
#install(TARGETS fetch DESTINATION ${CPU_INSTALL_LIB_DIR})
#install(FILES fetch.h DESTINATION ${CPU_INSTALL_INCLUDE_DIR})