#include "SMTPSampler.h"

#include <sstream>

namespace ISXBenchmark {

SMTPSampler::SMTPSampler() 
    : m_listener()
{}

SMTPSampler::~SMTPSampler()
{};

bool SMTPSampler::Setup(uint8_t timeout)
{
    m_timeout = timeout;
    return true;
}

void SMTPSampler::ExecuteInstance(uint32_t m_thread_id)
{
    SMTPContext smtp_context;
    smtp_context.Initialize();

    std::unique_ptr<ISXSC::SmtpClient> smtp_client = std::make_unique<ISXSC::SmtpClient>(smtp_context.io_context, smtp_context.ssl_context);
    smtp_client->SetTimeout(m_timeout);
    
    bool is_successful = true;
    TimerResults timer_results;
    double global_duration = MeasureDuration(PerformMailOperations, *smtp_client, timer_results, is_successful);

    delete smtp_client.release();
    smtp_context.Cleanup();

    m_listener.LogResult(m_thread_id, global_duration, timer_results, is_successful);  
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

void SMTPSampler::PerformMailOperations(ISXSC::SmtpClient& smtp_client, TimerResults& timer_results, bool& is_successful)
{
    try
    {   
        timer_results.establish_connection_duration = MeasureDuration([&]() {
            smtp_client.AsyncConnect("127.0.0.1", 2525).get();
        });

        timer_results.auth_duration =  MeasureDuration([&]() {
            smtp_client.AsyncAuthenticate("user@gmail.com", "password").get();
        });

        std::string subject = "C++ benchmark subject " + CurrentTimeToString();
        ISXMM::MailMessageBuilder mail_builder;
        mail_builder.set_from("user@gmail.com")
            .add_to("user@gmail.com")
            .set_subject(subject)
            .set_body("C++ benchmark body");

        timer_results.send_mail_duration = MeasureDuration([&]() {
            smtp_client.AsyncSendMail(mail_builder.Build()).get();
        });
    } 
    catch (const std::exception& e)
    {
        is_successful = false;
    }
}
}