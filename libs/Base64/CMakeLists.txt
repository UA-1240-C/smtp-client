cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

add_library(Base64 STATIC)

target_sources(Base64 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Base64.cpp
)

target_include_directories(Base64 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)