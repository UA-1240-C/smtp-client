#include "ThreadManager.h"
#include "SMTPSampler.h"

using namespace ISXBenchmark;

int main()
{
    uint16_t thread_number = 20;
    std::chrono::duration<double> ramp_up_period(1);
    uint16_t loop_count = 1;
    ThreadManager tm(thread_number, ramp_up_period, loop_count, std::make_unique<SMTPSampler>());

    uint16_t client_timeout = 2;
    std::cout << tm.Start(client_timeout) << std::endl;
}
