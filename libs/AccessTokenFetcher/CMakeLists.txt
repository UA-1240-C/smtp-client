cmake_minimum_required(VERSION 3.0)

project(AccessTokenFetcher VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

add_library(AccessTokenFetcher STATIC)

target_sources(AccessTokenFetcher PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AccessTokenFetcher.cpp
)

target_include_directories(AccessTokenFetcher PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${JSONCPP_INCLUDE_DIRS}
    ../Base64/include
)

target_link_libraries(AccessTokenFetcher PUBLIC
    ${JSONCPP_LIBRARIES}
    Base64
)

