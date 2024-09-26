cmake_minimum_required(VERSION 3.10)

project(Benchmark VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

add_library(Benchmark STATIC)


target_sources(Benchmark PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ThreadManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SMTPSampler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Utils.cpp
)

target_include_directories(Benchmark PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Benchmark PUBLIC
    SmartSocket
    SMTP_client
    MailMessage
)