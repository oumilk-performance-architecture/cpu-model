project(arm_cpu)

set(SOURCE_FILES main.cpp main.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(utils/uop)
target_link_libraries(${PROJECT_NAME} uop)
target_include_directories(${PROJECT_NAME} PRIVATE utils/uop)

add_subdirectory(utils/uinstr)
target_link_libraries(${PROJECT_NAME} uinstr)
target_include_directories(${PROJECT_NAME} PRIVATE utils/uinstr)

add_subdirectory(utils/func)
target_link_libraries(${PROJECT_NAME} func)
target_include_directories(${PROJECT_NAME} PRIVATE utils/func)

add_subdirectory(utils/isa)
target_link_libraries(${PROJECT_NAME} isa)
target_include_directories(${PROJECT_NAME} PRIVATE utils/isa)

add_subdirectory(bus)
target_link_libraries(${PROJECT_NAME} bus)
target_include_directories(${PROJECT_NAME} PRIVATE bus)

add_subdirectory(core)
target_link_libraries(${PROJECT_NAME} core)
target_include_directories(${PROJECT_NAME} PRIVATE core)

install(TARGETS arm_cpu DESTINATION ${CPU_INSTALL_BIN_DIR})
#install(FILES main.h DESTINATION ${CPU_INSTALL_INCLUDE_DIR})