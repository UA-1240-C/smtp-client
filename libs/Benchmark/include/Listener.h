#pragma once

#include <mutex>
#include <iostream>
#include <fstream>

#include "Utils.h"

namespace ISXBenchmark {

class Listener {
public:
    static Listener& GetInstance();

    void LogResult(int thread_id, double time_taken, TimerResults& results, bool success);

private:
    Listener() = default;
    std::mutex m_mutex; 
};

}