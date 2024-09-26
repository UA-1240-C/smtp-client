#pragma once

#include <mutex>
#include <iostream>
#include <fstream>

class Listener {
public:
    static Listener& getInstance() {
        static Listener instance;
        return instance;
    }

    void logResult(int thread_id, double time_taken, bool success) {
        std::lock_guard<std::mutex> lock(mutex_);
        std::ofstream log_file("results.log", std::ios::app);
        log_file << "Thread " << thread_id << ": Time = " << time_taken << "s, Success = " << success << "\n";
        log_file.close();
    }

private:
    Listener() = default;
    std::mutex mutex_;  // For thread-safe logging
};
