#pragma once 

#include <string>
#include <regex>

#include "StatusType.h"


class SMTPResponse {
public:
    explicit SMTPResponse(const std::string& response);

    u_int16_t get_code() const;
    std::string get_enhanced_code() const;
    std::string get_text() const;

    StatusType get_status() const;
    bool CodeEquals(u_int16_t code) const;
    bool StatusEquals(StatusType status) const;

private:
    u_int16_t m_code;
    std::string m_enhanced_code;
    std::string m_text;
    StatusType m_status;

    void ParseResponse(const std::string& response);
};