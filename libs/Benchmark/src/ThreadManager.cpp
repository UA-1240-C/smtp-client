#include "ThreadManager.h"

namespace ISXBenchmark {

ThreadManager::ThreadManager(uint16_t num_threads, std::chrono::duration<double> ramp_up_period,
                             uint16_t loop_count, std::unique_ptr<Sampler> sampler)
    : NUM_THREADS(num_threads), RAMP_UP_PERIOD(ramp_up_period),
        LOOP_COUNT(loop_count), m_sampler(std::move(sampler)) {}

std::string ThreadManager::Start() 
{
    if (!m_sampler->Setup()) 
    {
        std::cerr << "Failure during setup of sampler\n";
        return "Failure during setup of sampler\n";
    }

    auto delay = RAMP_UP_PERIOD / NUM_THREADS;

    for (uint16_t i = 0; i < LOOP_COUNT; i++) 
    {
        for (uint16_t i = 0; i < NUM_THREADS; ++i) 
        {
            m_threads.emplace_back(&ThreadManager::Run, this, i, std::ref(*m_sampler));
            std::this_thread::sleep_for(delay);
        }

        for (auto& thread : m_threads) {
            thread.join();
        }
    }
    return m_sampler->CalculateStatistics();
}

void ThreadManager::Run(uint16_t thread_id, Sampler& sampler) 
{
    sampler.ExecuteInstance(thread_id);
}

}