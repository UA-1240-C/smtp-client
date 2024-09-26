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
    double ehlo_duration;
    double auth_duration;
    double send_mail_duration;

    TimerResults();
};

std::ostream& operator<<(std::ostream& os, const TimerResults& results);

struct SamplerResults
{
    double total_duration;
    TimerResults commands_duration;
    bool is_successful;
};

}