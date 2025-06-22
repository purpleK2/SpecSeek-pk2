#include <system/hardware/CPU/cpu.h>
#include <system/hardware/CPU/specifications.h>
#include <utils/terminal.h>
#include <stdio.h>

/// @brief INTEL ONLY gets the amount of threads per CPU physical Core
/// @return threads per core
unsigned int intel_cpu_get_threads_per_core(void) {
    return 0;
}

/// @brief INTEL ONLY Gets the logical processor count for the CPU Package
/// @return Logicial Processor Count
unsigned int intel_cpu_get_logical_processor_count(void) {
    if (cpu_get_max_supported_leaf() >= 0x0000001F){
        
    }else if (cpu_get_max_supported_leaf() >= 0x0000000B){
        unsigned int eax, ebx, ecx, edx;
        cpuid(0x0000000B, 0, &eax, &ebx, &ecx, &edx);
        unsigned int level_type = (ecx >> 8) & 0xFF;

        if (level_type == 2 && ebx > 0){
            return ebx;
        } else{
            printf("%s%s:%d SpecSeek fell out of the level type check\nThis error is fatal, please report at https://github.com/Mellurboo/SpecSeek", BRED, __FILE__, __LINE__);
            return 0;
        }
    }
    return 0;
}

/// @brief 
/// @return 
unsigned int intel_cpu_get_physical_core_count(void) {
    return 0;
}