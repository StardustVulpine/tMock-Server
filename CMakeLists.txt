cmake_minimum_required(VERSION 4.1)
project(terraria_mock_server)

set(CMAKE_CXX_STANDARD 26)

add_executable(terraria_mock_server main.cpp
        structs/messages.hpp
        classes/Socket.cpp
        classes/Socket.h
        enums/AdressFamily.h
        enums/ConnectionType.h
        classes/Exception.cpp
        classes/Exception.h
        classes/Log.cpp
        classes/Log.h
)

TARGET_INCLUDE_DIRECTORIES(terraria_mock_server PRIVATE classes enums structs)