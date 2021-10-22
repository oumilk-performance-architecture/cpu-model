project(reservation C CXX)

set(SOURCE_FILES
reservation.h
reservation.cpp
)

add_library(${PROJECT_NAME} SHARED STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} uinstr)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/utils/uinstr)

#install(TARGETS fetch DESTINATION ${CPU_INSTALL_LIB_DIR})
#install(FILES fetch.h DESTINATION ${CPU_INSTALL_INCLUDE_DIR})