#ifndef TEST_HELPERS_HPP_
#define TEST_HELPERS_HPP_

#pragma once
#include <iostream>
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
        std::cout << "\033[31m"
                  << "TESTS FAILED"
                  << "\033[0m"
                  << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "\033[32m"
              << "TESTS PASSED!"
              << "\033[0m"
              << std::endl;
    return EXIT_SUCCESS;
}

#endif // TEST_HELPERS_HPP_