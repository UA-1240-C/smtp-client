#pragma once

#include <mutex>
#include <iostream>
#include <fstream>
#include <vector>

#include "Utils.h"

namespace ISXBenchmark {

class Listener {
public:
    Listener() = default;

    void LogResult(int thread_id, double time_taken, TimerResults& results, bool success);

    const std::vector<SamplerResults>& get_results() const {return m_results;}

private:
    std::mutex m_mutex; 
    std::vector<SamplerResults> m_results;
};

}