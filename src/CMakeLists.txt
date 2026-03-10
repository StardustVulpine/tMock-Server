cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 26)

set(EXECUTABLES_LIST
        main.cpp
        Server.cpp
)
add_executable(${PROJECT_NAME} ${EXECUTABLES_LIST})

set(LIB_LINK_TARGETS
        tmock_networking
        tmock_communication
        tmock_terraria
        console_logger
)
target_link_libraries(${PROJECT_NAME} ${LIB_LINK_TARGETS})
add_dependencies(${PROJECT_NAME} ${LIB_LINK_TARGETS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/ext)