#include "../../include/system_stats/cpu_stats.h"
#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <string>
#include <regex>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

CPUStats::CPUStats() : conn(0) {
}

CPUStats::~CPUStats() {
}

double CPUStats::getCPUTemperature() const {
    try {
        // htop에서 CPU 온도 정보를 가져옵니다
        std::string result = exec("htop -C | head -n 2");
        
        // 정규식을 사용하여 온도 값을 추출
        std::regex temp_regex("Temp:\\s*(\\d+)°C");
        std::smatch matches;
        if (std::regex_search(result, matches, temp_regex) && matches.size() > 1) {
            return std::stod(matches[1].str());
        }
    } catch (const std::exception& e) {
        std::cerr << "Error reading CPU temperature: " << e.what() << std::endl;
    }
    
    return 0.0;
}

bool CPUStats::updateTemperature() {
    return getCPUTemperature() > 0;
} 