#include "ThreadManager.h"
#include "SMTPSampler.h"

using namespace ISXBenchmark;

int main()
{
    ThreadManager tm(40, std::chrono::duration<double>(1), 1, std::make_unique<SMTPSampler>());
    std::cout << tm.Start(20) << std::endl;
}
