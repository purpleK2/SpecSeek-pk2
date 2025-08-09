#define _GNU_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <system/hardware/CPU/affinity.h>

#if defined(__linux__)
#include <sched.h>
#include <unistd.h>
#endif
#if defined(_WIN32)
#include <windows.h>
#endif

/// @brief pins the thread to a defined cpu core using its APIC core ID
/// @param apic_core_id target CPU core APIC ID
/// @return success 0/1
int cpu_set_affinity(int apic_core_id){
    #if defined(__linux__)
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(apic_core_id, &set);
    return sched_setaffinity(0, sizeof(set), &set);
    #endif

    #if defined(_WIN32)
    DWORD_PTR mask = 1ULL << apic_core_id;
    HANDLE thread = GetCurrentThread();
    DWORD_PTR result = SetThreadAffinityMask(thread, mask);
    if (result == 0) {
        fprintf(stderr, "Failed to set thread affinity: %lu\n", GetLastError());
        return 1;
    }

    return 0;
    #endif

    return 1;
}
