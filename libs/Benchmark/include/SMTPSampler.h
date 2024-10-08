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
    Listener m_listener;

    struct DurationStats {
        double min_duration = std::numeric_limits<double>::max();
        double max_duration = std::numeric_limits<double>::lowest();
        double sum_duration = 0;
        int valid_count = 0;
        int negative_count = 0;

        void Update(double duration);
    };

    struct SMTPContext
    {
        boost::asio::io_context io_context;
        boost::asio::ssl::context ssl_context;
        std::thread worker;

        SMTPContext() : ssl_context(boost::asio::ssl::context::tls_client)
        {}

        ~SMTPContext() {
            Cleanup();
        } 

        void Initialize()
        {
            ssl_context.set_verify_mode(boost::asio::ssl::verify_none);

            worker = std::thread([&]() {
                asio::io_context::work work(io_context);
                io_context.run();
            });
        }

        void Cleanup()
        {
            if (!io_context.stopped())
                io_context.stop();

            if (worker.joinable())
                worker.join();
        }
    };

    static void PrintStats(std::ostream& os, const std::string& name, const DurationStats& stats);

    static void PerformMailOperations(ISXSC::SmtpClient& smtp_client, TimerResults& timer_results, bool& is_successful);

};

}
