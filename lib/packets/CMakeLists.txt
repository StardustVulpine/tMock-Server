cmake_minimum_required(VERSION 4.1)
project(tmock_communication)

set(CMAKE_CXX_STANDARD 26)

set(LIB_SOURCES
        include/Packets.hpp

        src/BasePacket.hpp
        src/ConnectRequest.hpp
        src/FatalError.hpp
        src/RequestPassword.hpp
        src/SendPassword.hpp
        src/ConnectionApproved.hpp

        src/BasePacket.cpp
        src/ConnectRequest.cpp
        src/FatalError.cpp
        src/RequestPassword.cpp
        src/SendPassword.cpp
        src/ConnectionApproved.cpp
)
add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})

set(LIB_LINK_TARGETS
        tmock_networking
)
target_link_libraries(${PROJECT_NAME} ${LIB_LINK_TARGETS})
add_dependencies(${PROJECT_NAME} ${LIB_LINK_TARGETS})

set(INCLUDE_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})