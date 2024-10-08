#include "ThreadManager.h"
#include "SMTPSampler.h"

using namespace ISXBenchmark;

int main()
{
    ThreadManager tm(10, std::chrono::duration<double>(1), 1, std::make_unique<SMTPSampler>());
    std::cout << tm.Start(1) << std::endl;
}
