#pragma once

#include <chrono>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "SmartSocket.h"

#include "Listener.h"

class SMTPSampler {
public:
    SMTPSampler(uint32_t thread_id, boost::asio::io_context& io_context,
                boost::asio::ssl::context& ssl_context)
     : m_thread_id(thread_id), m_io_context(io_context),
       m_ssl_context(ssl_context) 
    {}

    void ExecuteInstance() {
        auto start = std::chrono::high_resolution_clock::now();
        
        // Simulate email sending
        // [You would put your SMTP email sending logic here, using Boost.Asio or similar]

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        // Send result to Listener
        Listener::getInstance().logResult(m_thread_id, elapsed.count(), true);  // true = success
    }

private:
    uint32_t m_thread_id;
    boost::asio::io_context& m_io_context;
    boost::asio::ssl::context& m_ssl_context;
};
