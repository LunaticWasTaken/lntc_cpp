cmake_minimum_required(VERSION 3.31)
project(lntc_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(${PROJECT_NAME}_test "${CMAKE_SOURCE_DIR}/test/test.cpp")
endif ()
