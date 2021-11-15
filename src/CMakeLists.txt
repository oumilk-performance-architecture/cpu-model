project(riscv_cpu)

set(SOURCE_FILES main.cpp main.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(utils/common)
target_link_libraries(${PROJECT_NAME} common)
target_include_directories(${PROJECT_NAME} PRIVATE utils/common)

add_subdirectory(utils/uop)
target_link_libraries(${PROJECT_NAME} uop)
target_include_directories(${PROJECT_NAME} PRIVATE utils/uop)

add_subdirectory(utils/idata)
target_link_libraries(${PROJECT_NAME} idata)
target_include_directories(${PROJECT_NAME} PRIVATE utils/idata)

add_subdirectory(utils/uinstr)
target_link_libraries(${PROJECT_NAME} uinstr)
target_include_directories(${PROJECT_NAME} PRIVATE utils/uinstr)

add_subdirectory(instruction/func)
target_link_libraries(${PROJECT_NAME} func)
target_include_directories(${PROJECT_NAME} PRIVATE instruction/func)

add_subdirectory(instruction/isa)
target_link_libraries(${PROJECT_NAME} decoder)
target_include_directories(${PROJECT_NAME} PRIVATE instruction/isa)

add_subdirectory(instruction/portbind)
target_link_libraries(${PROJECT_NAME} portbind)
target_include_directories(${PROJECT_NAME} PRIVATE instruction/portbind)

add_subdirectory(utils/parameter)
target_link_libraries(${PROJECT_NAME} parameter)
target_include_directories(${PROJECT_NAME} PRIVATE utils/parameter)

add_subdirectory(utils/delay)
target_link_libraries(${PROJECT_NAME} delay)
target_include_directories(${PROJECT_NAME} PRIVATE utils/delay)

add_subdirectory(bus)
target_link_libraries(${PROJECT_NAME} bus)
target_include_directories(${PROJECT_NAME} PRIVATE bus)

add_subdirectory(core)
target_link_libraries(${PROJECT_NAME} core)
target_include_directories(${PROJECT_NAME} PRIVATE core)

install(TARGETS riscv_cpu DESTINATION ${CPU_INSTALL_BIN_DIR})
#install(FILES main.h DESTINATION ${CPU_INSTALL_INCLUDE_DIR})