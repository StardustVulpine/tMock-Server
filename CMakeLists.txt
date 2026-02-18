cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_STANDARD 26)
project(tmock_server)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_options(-Wall -Wextra -Werror)
    add_compile_definitions(DEBUG)
endif ()

# Libraries
add_subdirectory(lib/networking)
add_subdirectory(lib/packets)
add_subdirectory(lib/terraria)

# Executable
add_subdirectory(src "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(DIRECTORIES

)
if (${DIRECOTIRES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${DIRECTORIES})
endif ()

#file(COPY_FILE "${CMAKE_SOURCE_DIR}/server-cfg.json" "${CMAKE_BINARY_DIR}/server-cfg.json")
configure_file("${CMAKE_SOURCE_DIR}/cfg/server_config.json" "${CMAKE_BINARY_DIR}/bin/server_config.json")