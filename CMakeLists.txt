cmake_minimum_required(VERSION 4.0)
project(lntc_cpp)

set(CMAKE_CXX_STANDARD 23)

add_library(${PROJECT_NAME} STATIC lntc_cpp.hpp)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_executable(${PROJECT_NAME}_test "${CMAKE_SOURCE_DIR}/test/test.cpp")
endif ()