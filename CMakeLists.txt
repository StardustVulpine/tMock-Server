cmake_minimum_required(VERSION 4.1)
project(tmock_server)

set(CMAKE_CXX_STANDARD 26)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_options(-Wall -Wextra -Werror)
    add_compile_definitions(DEBUG)
endif ()

set(EXECUTABLES_LIST
        main.cpp
        extern_lib/json.hpp
        Configs.hpp
)
add_executable(${PROJECT_NAME} ${EXECUTABLES_LIST})

set(LIB_LINK_TARGETS
        tmock_networking
        tmock_packets
)
target_link_libraries(${PROJECT_NAME} ${LIB_LINK_TARGETS})
add_dependencies(${PROJECT_NAME} ${LIB_LINK_TARGETS})

add_subdirectory(networking)
add_subdirectory(packets)

set(DIRECTORIES

)

if (${DIRECOTIRES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${DIRECTORIES})
endif ()

#file(COPY_FILE "${CMAKE_SOURCE_DIR}/server-config.json" "${CMAKE_BINARY_DIR}/server-config.json")
configure_file("${CMAKE_SOURCE_DIR}/server-config.json" "${CMAKE_BINARY_DIR}/server-config.json")