#include "../../include/system_stats/memory_stats.h"
#include <mach/mach.h>
#include <mach/mach_host.h>
#include <sys/sysctl.h>
#include <iomanip>
#include <sstream>

MemoryStats::MemoryStats() {
    updateMemoryInfo();
}

MemoryStats::~MemoryStats() {
}

bool MemoryStats::updateMemoryInfo() {
    mach_msg_type_number_t count = HOST_VM_INFO_COUNT;
    vm_statistics_data_t vmstat;
    
    if (host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vmstat, &count) != KERN_SUCCESS) {
        return false;
    }

    // 페이지 크기 (일반적으로 4KB)
    uint64_t pageSize = vm_kernel_page_size;

    // 전체 메모리 크기를 가져옵니다
    int64_t total = 0;
    size_t len = sizeof(total);
    if (sysctlbyname("hw.memsize", &total, &len, NULL, 0) == -1) {
        return false;
    }

    // 각 메모리 상태의 페이지 수를 바이트로 변환
    uint64_t free = vmstat.free_count * pageSize;
    uint64_t active = vmstat.active_count * pageSize;
    uint64_t inactive = vmstat.inactive_count * pageSize;
    uint64_t wired = vmstat.wire_count * pageSize;

    currentInfo.total = total;
    currentInfo.free = free;
    currentInfo.used = active + wired;
    currentInfo.usedPercent = (double)(currentInfo.used) * 100.0 / currentInfo.total;

    return true;
}

MemoryInfo MemoryStats::getMemoryInfo() const {
    return currentInfo;
}

std::string MemoryStats::formatSize(uint64_t bytes) const {
    const char* units[] = {"B", "KB", "MB", "GB", "TB"};
    int unitIndex = 0;
    double size = bytes;

    while (size >= 1024 && unitIndex < 4) {
        size /= 1024;
        unitIndex++;
    }

    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << size << " " << units[unitIndex];
    return ss.str();
} 