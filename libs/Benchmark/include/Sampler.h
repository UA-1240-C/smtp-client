#pragma once

#include <cstdint>

namespace ISXBenchmark {

class Sampler 
{
public:
    Sampler() = default;
    virtual ~Sampler() = default;

    virtual bool Setup() = 0;
    virtual void ExecuteInstance(uint32_t m_thread_id) = 0;
};

}