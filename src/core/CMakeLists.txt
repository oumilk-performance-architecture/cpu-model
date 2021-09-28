project(core C CXX)

set(SOURCE_FILES core.h core.cpp)
add_library(${PROJECT_NAME} SHARED STATIC ${SOURCE_FILES})

add_subdirectory(state)
#target_link_libraries(${PROJECT_NAME} state)
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/core/state)

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

target_link_libraries(${PROJECT_NAME} uinstr)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uinstr)

#target_link_libraries(${PROJECT_NAME} isa)
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/instruction/isa)

# REMOVE ME - JOU
target_link_libraries(${PROJECT_NAME} func)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/instruction/func)

target_link_libraries(${PROJECT_NAME} uop)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uop)

#target_link_libraries(${PROJECT_NAME} portbind)
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/instruction/portbind)

#target_link_libraries(${PROJECT_NAME} idata)
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/idata)

target_link_libraries(${PROJECT_NAME} parameter)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/parameter)

target_link_libraries(${PROJECT_NAME} delay)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/delay)

target_link_libraries(${PROJECT_NAME} bus)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/bus)
#install(TARGETS core DESTINATION ${CPU_INSTALL_LIB_DIR})
#install(FILES core.h DESTINATION ${CPU_INSTALL_INCLUDE_DIR})