cmake_minimum_required(VERSION 4.1)
project(terraria_mock_server)

set(CMAKE_CXX_STANDARD 26)

add_executable(terraria_mock_server main.cpp
        structs/messages.hpp
        classes/Socket.cpp
        classes/Socket.hpp
        enums/AddressFamily.h
        enums/ConnectionType.h
        classes/Exception.cpp
        classes/Exception.hpp
        classes/Log.cpp
        classes/Log.hpp
        classes/messages/BaseMessage.cpp
        classes/messages/BaseMessage.hpp
        classes/messages/ConnectRequest.cpp
        classes/messages/ConnectRequest.hpp
)

TARGET_INCLUDE_DIRECTORIES(terraria_mock_server PRIVATE classes enums structs)