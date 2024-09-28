#pragma once

#include <vector>
#include <thread>
#include <chrono>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "SMTPSampler.h"
#include "Sampler.h"

namespace ISXBenchmark {

class ThreadManager {
public:
    ThreadManager(uint16_t num_threads, std::chrono::duration<double> ramp_up_period,
                  uint16_t loop_count, std::unique_ptr<Sampler> sampler);

    std::string Start();

private:
    void Run(uint16_t thread_id, Sampler& sampler);

    const uint16_t NUM_THREADS;
    const std::chrono::duration<double> RAMP_UP_PERIOD;
    const uint16_t LOOP_COUNT;
    std::vector<std::thread> m_threads;
    std::unique_ptr<Sampler> m_sampler;
    
};

}
