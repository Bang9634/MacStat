#ifndef MEMORY_STATS_H
#define MEMORY_STATS_H

#include <cstdint>
#include <string>

struct MemoryInfo {
    uint64_t total;      // 전체 메모리
    uint64_t used;       // 사용 중인 메모리
    uint64_t free;       // 사용 가능한 메모리
    double usedPercent;  // 사용률 (%)
};

class MemoryStats {
public:
    MemoryStats();
    ~MemoryStats();

    MemoryInfo getMemoryInfo() const;
    bool updateMemoryInfo();
    std::string formatSize(uint64_t bytes) const;

private:
    MemoryInfo currentInfo;
};

#endif // MEMORY_STATS_H 