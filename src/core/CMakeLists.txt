project(core C CXX)

set(SOURCE_FILES core.h core.cpp)
add_library(${PROJECT_NAME} SHARED STATIC ${SOURCE_FILES})

add_subdirectory(fetch)
target_link_libraries(${PROJECT_NAME} fetch)
target_include_directories(${PROJECT_NAME} PRIVATE fetch)

target_link_libraries(${PROJECT_NAME} uinstr)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uinstr)

target_link_libraries(${PROJECT_NAME} isa)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/isa)

target_link_libraries(${PROJECT_NAME} uop)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uop)

target_link_libraries(${PROJECT_NAME} parameter)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/parameter)
#install(TARGETS core DESTINATION ${CPU_INSTALL_LIB_DIR})
#install(FILES core.h DESTINATION ${CPU_INSTALL_INCLUDE_DIR})