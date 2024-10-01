#include "SMTPSampler.h"

#include <sstream>

namespace ISXBenchmark {

SMTPSampler::SMTPSampler() 
    : m_io_context(), m_ssl_context(boost::asio::ssl::context::tls_client),
      m_listener()
{}

SMTPSampler::~SMTPSampler()
{
    if (!m_io_context.stopped())
        m_io_context.stop();

    if (m_worker.joinable())
        m_worker.join();
};

bool SMTPSampler::Setup(uint8_t timeout)
{
    m_timeout = timeout;
    try
    {
        m_ssl_context.set_verify_mode(boost::asio::ssl::verify_none);
        m_worker = std::thread(
            [&m_io_context = this->m_io_context]() {
                boost::asio::io_context::work work(m_io_context);
                m_io_context.run();
        });
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

void SMTPSampler::ExecuteInstance(uint32_t m_thread_id)
{
    Timer timer_global;
    
    std::unique_ptr<ISXSC::SmtpClient> smtp_client = std::make_unique<ISXSC::SmtpClient>(m_io_context, m_ssl_context);
    smtp_client->SetTimeout(m_timeout);
    bool is_successful = true;

    TimerResults timer_results;

    try
    {   
        timer_results.establish_connection_duration = MeasureDuration([&]() {
            smtp_client->AsyncConnect("127.0.0.1", 2525).get();
        });

        timer_results.auth_duration =  MeasureDuration([&]() {
            smtp_client->AsyncAuthenticate("user@gmail.com", "password").get();
        });

        std::string subject = "C++ benchmark subject " + CurrentTimeToString();
        ISXMM::MailMessageBuilder mail_builder;
        mail_builder.set_from("user@gmail.com")
            .add_to("user@gmail.com")
            .set_subject(subject)
            .set_body("C++ benchmark body");

        timer_results.send_mail_duration = MeasureDuration([&]() {
            smtp_client->AsyncSendMail(mail_builder.Build()).get();
        });

        delete smtp_client.release();
    } 
    catch (const std::exception& e)
    {
        is_successful = false;
    }
    delete smtp_client.release();

    m_listener.LogResult(m_thread_id, timer_global.GetDuration(), timer_results, is_successful);  // true = success
}

std::string SMTPSampler::CalculateStatistics()
{
    auto results = m_listener.get_results();

    int total_samples = results.size();
    int error_count = 0;

    DurationStats total_stats, establishing_connection_stats, auth_stats, send_stats;

    for (const auto& sample : results) {
        if (!sample.is_successful) {
            error_count++;
        } else {
            total_stats.Update(sample.total_duration);

            establishing_connection_stats.Update(sample.commands_duration.establish_connection_duration);
            auth_stats.Update(sample.commands_duration.auth_duration);
            send_stats.Update(sample.commands_duration.send_mail_duration);
        }
    }

    double error_percentage = (static_cast<double>(error_count) / total_samples) * 100.0;

    std::stringstream ss;

    ss << "Error percentage: " << error_percentage << "%\n";

    PrintStats(ss, "Total", total_stats);
    PrintStats(ss, "Establishing connnection", establishing_connection_stats);
    PrintStats(ss, "AUTH", auth_stats);
    PrintStats(ss, "SEND_MAIL", send_stats);
    
    return ss.str();
}

void SMTPSampler::DurationStats::Update(double duration) {
    if (duration >= 0) {
        sum_duration += duration;
        min_duration = std::min(min_duration, duration);
        max_duration = std::max(max_duration, duration);
        valid_count++;
    } else {
        negative_count++;
    }
}

void SMTPSampler::PrintStats(std::ostream& os, const std::string& name, const SMTPSampler::DurationStats& stats) {
    if (stats.valid_count > 0) {
        os << name << " Duration - Min: " << stats.min_duration
                << ", Max: " << stats.max_duration
                << ", Avg: " << stats.sum_duration / stats.valid_count << '\n';
    }
    os << name << " negative count: " << stats.negative_count << '\n';
}

}