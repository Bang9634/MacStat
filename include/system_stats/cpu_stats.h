#ifndef CPU_STATS_H
#define CPU_STATS_H

#include <string>

class CPUStats {
public:
    CPUStats();
    ~CPUStats();

    double getCPUTemperature() const;
    bool updateTemperature();

private:
    int conn;  // 호환성을 위해 유지
};

#endif // CPU_STATS_H