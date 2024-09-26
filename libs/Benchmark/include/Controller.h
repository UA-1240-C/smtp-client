#pragma once

#include <iostream>

class Controller {
public:
    Controller(int max_loops, int max_failures)
        : max_loops_(max_loops), max_failures_(max_failures), failures_(0), loops_(0) {}

    void checkTestLogic() {
        // Check if we need to stop based on max loops or failures
        if (loops_ >= max_loops_ || failures_ >= max_failures_) {
            stopTest();
        }
        loops_++;
    }

    void reportFailure() {
        failures_++;
    }

    void stopTest() {
        // Logic to stop the test (like interrupting threads)
        std::cout << "Test stopped due to test logic conditions." << std::endl;
        exit(0);  // Simplified exit logic
    }

private:
    int max_loops_;
    int max_failures_;
    int failures_;
    int loops_;
};
