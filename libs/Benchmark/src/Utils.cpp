#include "Utils.h"

namespace ISXBenchmark {

std::ostream& operator<<(std::ostream& os, const TimerResults& results) {
    os << "EHLO Duration: " << results.establish_connection_duration << "s; ";
    os << "Auth Duration: " << results.auth_duration << "s; ";
    os << "Send Mail Duration: " << results.send_mail_duration << "s ;";
    return os;
}

Timer::Timer() : m_start_time(std::chrono::high_resolution_clock::now())
{}
double Timer::GetDuration() const
{
    std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - m_start_time;
    return duration.count();
}

TimerResults::TimerResults() : establish_connection_duration(-1), auth_duration(-1), send_mail_duration(-1) {}


std::string CurrentTimeToString() 
{    
    auto now = std::chrono::high_resolution_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_time_t), "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

SamplerResults::SamplerResults(double total_duration, TimerResults& commands_duration, bool is_successful)
 : total_duration(total_duration), commands_duration(commands_duration),
   is_successful(is_successful)
   {

   }

}