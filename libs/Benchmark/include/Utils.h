#pragma once

#include <iostream>
#include <chrono>
#include <ctime>   
#include <iomanip>  
#include <sstream>  

namespace ISXBenchmark {

std::string CurrentTimeToString();

class Timer 
{
public:
    Timer();
    double GetDuration() const;
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time;
};

struct TimerResults 
{
    double establish_connection_duration;
    double auth_duration;
    double send_mail_duration;

    TimerResults();
};

template<typename Func, typename... Args>
inline double MeasureDuration(Func&& func, Args&&... args) {
    Timer timer;
    std::forward<Func>(func)(std::forward<Args>(args)...);
    return timer.GetDuration();
}

std::ostream& operator<<(std::ostream& os, const TimerResults& results);

struct SamplerResults
{
    double total_duration;
    TimerResults commands_duration;
    bool is_successful;

    SamplerResults(double total_duration, TimerResults& commands_duration, bool is_successful);
};

}