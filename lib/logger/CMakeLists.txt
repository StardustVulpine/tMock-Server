cmake_minimum_required(VERSION 4.1)
project(console_logger)

set(CMAKE_CXX_STANDARD 26)

set(LIB_SOURCES
        include/Log.hpp
        Log.cpp
)

add_library(${PROJECT_NAME} SHARED ${LIB_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include)