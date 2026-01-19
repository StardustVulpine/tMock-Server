cmake_minimum_required(VERSION 4.1)
project(terraria_mock_server)

set(CMAKE_CXX_STANDARD 26)

add_executable(terraria_mock_server main.cpp
        # Enums
        enums/AddressFamily.h
        enums/ConnectionType.h
        enums/MessageTypes.h
        enums/TextModes.h

        # Classes
        classes/Socket.cpp
        classes/Socket.hpp
        classes/Exception.cpp
        classes/Exception.hpp
        classes/Log.cpp
        classes/Log.hpp
        classes/Messages.hpp
        classes/messages/BaseMessage.cpp
        classes/messages/BaseMessage.hpp
        classes/messages/ConnectRequest.cpp
        classes/messages/ConnectRequest.hpp
        classes/messages/FatalErrorMessage.cpp
        classes/messages/FatalErrorMessage.hpp
        classes/messages/RequestPasswordMessage.cpp
        classes/messages/RequestPasswordMessage.hpp
        classes/messages/RecievePasswordMessage.cpp
        classes/messages/RecievePasswordMessage.hpp
)

TARGET_INCLUDE_DIRECTORIES(terraria_mock_server PRIVATE classes enums structs)