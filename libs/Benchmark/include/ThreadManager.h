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

    void Start();

private:
    void Run(uint16_t thread_id, Sampler& sampler);

    uint16_t m_num_threads;
    std::chrono::duration<double> m_ramp_up_period;
    uint16_t m_loop_count;
    std::vector<std::thread> m_threads;
    std::unique_ptr<Sampler> m_sampler;
    
};

}
