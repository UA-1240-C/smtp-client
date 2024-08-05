
add_library(SendUtilities
    src/SendUtilities.cpp
    src/File.cpp)

target_include_directories(SendUtilities PUBLIC include)

target_link_libraries(SendUtilities MailMessage SmartSocket Base64)