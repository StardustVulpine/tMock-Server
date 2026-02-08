cmake_minimum_required(VERSION 4.1)
project(tmock_networking)

set(CMAKE_CXX_STANDARD 26)

set(LIB_SOURCES
        include/AddressFamily.hpp
        include/ConnectionType.hpp
        include/Socket.hpp
        include/Exception.hpp

        src/Socket.cpp
        src/Exception.cpp
)

add_library(${PROJECT_NAME} SHARED ${LIB_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include src)

