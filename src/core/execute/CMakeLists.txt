project(execute C CXX)

set(SOURCE_FILES
execute.h
execute.cpp
)

add_library(${PROJECT_NAME} SHARED STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} parameter)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/parameter)

target_link_libraries(${PROJECT_NAME} register)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/core/register)

target_link_libraries(${PROJECT_NAME} delay)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/delay)

target_link_libraries(${PROJECT_NAME} uinstr)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uinstr)

add_subdirectory(reservation)
target_link_libraries(${PROJECT_NAME} reservation)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/core/execute/reservation/reservation)

#install(TARGETS fetch DESTINATION ${CPU_INSTALL_LIB_DIR})
#install(FILES fetch.h DESTINATION ${CPU_INSTALL_INCLUDE_DIR})