#pragma once

#include <boost/system/error_code.hpp>
#include <boost/asio.hpp>
#include <iostream>

#include "SMTPResponse.h"

using std::string;

namespace ISXLogs
{
class SmartSocketMethodsHandlers
{
public:
    static bool HandleConnection(
        const string& server, const int port
        , const boost::system::error_code& error_code);

    static bool HandleRemoteEndpointOp(
        const boost::system::error_code& error_code);

    static bool HandleWrite(
        const string& data
        , const boost::system::error_code& error_code);

    static ISXResponse::SMTPResponse HandleRead(
        boost::asio::streambuf& buffer
        , const boost::system::error_code& error_code);

    static bool HandleClose(
        const boost::system::error_code& error_code
        , bool* ssl_toggle);

    static bool HandleUpgradeSecurity(
        const boost::system::error_code& error_code
        , bool* ssl_toggle);

private:
    static inline void HandleError(
        const string& prefix, const boost::system::error_code& error_code);
    
    static inline void HandleTimeout(
        const boost::system::error_code& error_code);
        
    SmartSocketMethodsHandlers() = delete;
    ~SmartSocketMethodsHandlers() = delete;

    SmartSocketMethodsHandlers(const SmartSocketMethodsHandlers&) = delete;
    SmartSocketMethodsHandlers& operator=(const SmartSocketMethodsHandlers&) = delete;

    SmartSocketMethodsHandlers(SmartSocketMethodsHandlers&&) = delete;
    SmartSocketMethodsHandlers& operator=(SmartSocketMethodsHandlers&&) = delete;

    static inline std::ostream* s_log_stream = &std::clog;
};
}; // namespace ISXLogs