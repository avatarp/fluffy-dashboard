#pragma once
#include <memory>

struct TestResults {
    int32_t testCounter { 0 };
    int32_t passCounter { 0 };
    int32_t failCounter { 0 };
};

int verifyResults(TestResults& results)
{
    std::cout << results.testCounter << " tests run\n"
              << results.failCounter << " failed\n"
              << results.passCounter << " passed\n";
    if (results.failCounter > 0 || results.testCounter == 0) {
        std::cout << "TESTS FAILED" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "TESTS FAILED" << std::endl;
    return EXIT_SUCCESS;
}