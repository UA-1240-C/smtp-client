#pragma once

#include <chrono>
#include <memory>

#include <iostream>
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

    bool Setup(uint8_t timeout) override;

    void ExecuteInstance(uint32_t m_thread_id) override;

    std::string CalculateStatistics() override;

private:
    boost::asio::io_context m_io_context;
    boost::asio::ssl::context m_ssl_context;
    std::thread m_worker;
    Listener m_listener;

    struct DurationStats {
        double min_duration = std::numeric_limits<double>::max();
        double max_duration = std::numeric_limits<double>::lowest();
        double sum_duration = 0;
        int valid_count = 0;
        int negative_count = 0;

        void Update(double duration);
    };

    void PrintStats(std::ostream& os, const std::string& name, const DurationStats& stats);

};

}
