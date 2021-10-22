project(core C CXX)

set(SOURCE_FILES core.h core.cpp)
add_library(${PROJECT_NAME} SHARED STATIC ${SOURCE_FILES})

add_subdirectory(fetch)
target_link_libraries(${PROJECT_NAME} fetch)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/core/fetch)

add_subdirectory(decode)
target_link_libraries(${PROJECT_NAME} decode)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/core/decode)

add_subdirectory(allocate)
target_link_libraries(${PROJECT_NAME} allocate)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/core/allocate)

add_subdirectory(register)
target_link_libraries(${PROJECT_NAME} register)
target_include_directories(${PROJECT_NAME} PUBLIC register)

add_subdirectory(rename)
target_link_libraries(${PROJECT_NAME} rename)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/core/rename)

add_subdirectory(rob)
target_link_libraries(${PROJECT_NAME} rob)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/core/rob)

add_subdirectory(execute)
target_link_libraries(${PROJECT_NAME} execute)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/core/execute)

target_link_libraries(${PROJECT_NAME} uinstr)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uinstr)

# REMOVE ME - JOU
target_link_libraries(${PROJECT_NAME} func)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/instruction/func)

target_link_libraries(${PROJECT_NAME} uop)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uop)

target_link_libraries(${PROJECT_NAME} parameter)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/parameter)

target_link_libraries(${PROJECT_NAME} delay)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/delay)

target_link_libraries(${PROJECT_NAME} bus)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/bus)
