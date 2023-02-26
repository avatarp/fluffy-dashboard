#pragma once
#include <iostream>
#include <array>

inline std::string SystemCallForResponse(const char* cmd){
    std::array<char, 128> buffer;
    std::string result;
    auto pipe = popen(cmd, "r");

    if (!pipe) throw std::runtime_error("pipe - popen() failed!");

    while (!feof(pipe)){
        if(fgets(buffer.data(), 128, pipe) != nullptr)
            result += buffer.data();
    }

    ///TODO fix rc code not matching result code
    auto rc = pclose(pipe);

    if(rc == EXIT_SUCCESS)
    {
        std::clog<<"\nexit success"<<std::endl;
    }
    else if (rc == EXIT_FAILURE)
    {
        std::clog<<"\nexit failture"<<std::endl;
    }

    std::clog<<"\nresult for >"<<cmd<<"< was:\n" <<result<<std::endl;
    return result;
}
