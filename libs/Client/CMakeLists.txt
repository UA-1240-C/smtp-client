cmake_minimum_required(VERSION 3.10)

project(Client VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

# Add library target
add_library(SMTP_client STATIC)

target_sources(SMTP_client PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SmtpClient.cpp
)

target_include_directories(SMTP_client PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(SMTP_client PUBLIC
    ${Boost_LIBRARIES}
    SmartSocket
    Base64
    SMTPResponse
    MailMessage
    MessageSender
)