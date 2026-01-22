cmake_minimum_required(VERSION 4.1)
project(tmock_packets)

set(CMAKE_CXX_STANDARD 26)

set(LIB_SOURCES
        classes/BaseMessage.cpp
        classes/ConnectRequest.cpp
        classes/FatalError.cpp
        classes/RequestPassword.cpp
        classes/SendPassword.cpp
)
add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})

set(LIB_LINK_TARGETS
        tmock_networking
)
target_link_libraries(${PROJECT_NAME} ${LIB_LINK_TARGETS})
add_dependencies(${PROJECT_NAME} ${LIB_LINK_TARGETS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} enums classes)