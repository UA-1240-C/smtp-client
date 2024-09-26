#pragma once

#include <chrono>
#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "SmartSocket.h"
#include "SmtpClient.h"
#include "MailMessage.h"
#include "MailMessageBuilder.h"

#include "Listener.h"
#include "Sampler.h"
#include "Utils.h"

namespace ISXBenchmark {

class SMTPSampler final : public Sampler 
{
public:
    SMTPSampler();

    ~SMTPSampler() override;

    bool Setup() override;

    void ExecuteInstance(uint32_t m_thread_id) override;

private:
    boost::asio::io_context m_io_context;
    boost::asio::ssl::context m_ssl_context;
    std::thread m_worker;


};

}
