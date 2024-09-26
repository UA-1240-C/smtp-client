cmake_minimum_required(VERSION 3.10)

project(Benchmark VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

add_library(Benchmark STATIC)

# if(WIN32 AND MINGW)
#     message("Windows and mingw detected")
#     find_package(OpenSSL REQUIRED)

#     target_link_libraries(SmartSocket PUBLIC 
#         OpenSSL::SSL
#         OpenSSL::Crypto
#         ws2_32
#     )
# endif()



target_sources(Benchmark PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SmartSocket.cpp
)

target_include_directories(SmartSocket PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Benchmark PUBLIC
    SmartSocket
)