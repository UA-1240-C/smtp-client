#include "Listener.h"

namespace ISXBenchmark {


void Listener::LogResult(int thread_id, double time_taken, TimerResults& results, bool success) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_results.emplace_back(time_taken, results, success);
    std::ofstream log_file("../logs/results.log", std::ios::app);
    log_file << "Thread " << thread_id << ": Time = " << time_taken << "s, " << results <<" Success = " << success << "\n";
    log_file.close();
}

}