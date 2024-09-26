#pragma once

#include <vector>
#include <thread>
#include <chrono>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "SMTPSampler.h"
#include "Sampler.h"

class ThreadManager {
public:
    ThreadManager(uint16_t num_threads, std::chrono::duration<double> ramp_up_period,
                  uint16_t loop_count, std::unique_ptr<Sampler> sampler)
        : m_num_threads(num_threads), m_ramp_up_period(ramp_up_period),
          m_loop_count(loop_count), m_sampler(std::move(sampler)) {}

    void Start() {

        // SMTPSampler sampler;

        if (!m_sampler->Setup()) 
        {
            std::cerr << "Failure during setup of sampler\n";
            return;
        }

        auto delay = m_ramp_up_period / m_num_threads;

        for (uint16_t i = 0; i < m_loop_count; i++) 
        {
            for (uint16_t i = 0; i < m_num_threads; ++i) 
            {
                m_threads.emplace_back(&ThreadManager::Run, this, i, std::ref(*m_sampler));
                std::this_thread::sleep_for(delay);
            }

            for (auto& thread : m_threads) {
                thread.join();
            }
        }
    }

private:
    void Run(uint16_t thread_id, Sampler& sampler) {

        sampler.ExecuteInstance(thread_id);
    }

    uint16_t m_num_threads;
    std::chrono::duration<double> m_ramp_up_period;
    uint16_t m_loop_count;
    std::vector<std::thread> m_threads;
    std::unique_ptr<Sampler> m_sampler;
    
};
