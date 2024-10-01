#pragma once

#include <cstdint>

namespace ISXBenchmark {

class Sampler 
{
public:
    Sampler() = default;
    virtual ~Sampler() = default;

    virtual bool Setup(uint8_t timeout) = 0;
    virtual void ExecuteInstance(uint32_t m_thread_id) = 0;
    virtual std::string CalculateStatistics() = 0;

protected:
    uint8_t m_timeout;
};

}