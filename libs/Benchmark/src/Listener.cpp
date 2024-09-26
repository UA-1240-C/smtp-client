#include "Listener.h"

namespace ISXBenchmark {

Listener& Listener::GetInstance() {
    static Listener instance;
    return instance;
}

void Listener::LogResult(int thread_id, double time_taken, TimerResults& results, bool success) {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::ofstream log_file("results.log", std::ios::app);
    log_file << "Thread " << thread_id << ": Time = " << time_taken << "s, " << results <<" Success = " << success << "\n";
    log_file.close();
}

}