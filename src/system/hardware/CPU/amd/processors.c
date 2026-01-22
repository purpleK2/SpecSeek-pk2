#include <system/hardware/CPU/cpu.h>
#include <system/hardware/CPU/specifications.h>
#include <utils/terminal.h>
#include <stdio.h>

/// @brief AMD ONLY Implementaiton for getting the physical core count
/// @return int logical_processors / thread_per_core
unsigned int amd_cpu_get_physical_core_count(){
    unsigned int eax, ebx, ecx, edx;
    cpuid(0, 0, &eax, &ebx, &ecx, &edx);

    return amd_cpu_get_logical_processor_count() / amd_cpu_get_thread_count_per_core();
}

/// @brief AMD ONLY threads per cpu core
/// @return threads per core
unsigned int amd_cpu_get_thread_count_per_core(){
    unsigned int eax, ebx, ecx, edx;

    if (cpu_get_max_supported_extended_leaf() >= 0x1E){
        cpuid(0x8000001E, 0, &eax, &ebx, &ecx, &edx);
        unsigned int thread_count = (ebx >> 8) & 0xFF;
        return thread_count + 1;
    }else{
        IF_VERBOSE(2) printf("%sCPUID 0x8000001E Threads per Core Not supported\n", BRED);
        /*
            If we cant find the threads per core its probably becuase its either not
            Hyperthreaded or there its only 2 so AMD didnt bother documenting it much
            in this case we can just check if htt is enabled, if it is just assume its 2
            if not assume its 1. its not ideal, but probably accurate enough.
        */
        cpuid(0x00000001, 0, &eax, &ebx, &ecx, &edx);
        if (HAS_FEATURE(edx, 28)){
            IF_VERBOSE(2) printf("%sHyperthreading is enabled, assuming 2 threads per Core\n", BRED);
            return 2;
        }else{
            IF_VERBOSE(2) printf("%sHyperthreading is disabled, assuming 1 thread per Core\n", BRED);
            return 1;
        }
    }
}

unsigned int amd_cpu_get_nominal_core_clock(void){
    unsigned int eax, ebx, ecx, edx;

    if (!cpu_supports_extended_leaf(0x80000008)){
        return 0;
    }

    cpuid(0x80000008, 0, &eax, &ebx, &ecx, &edx);

    unsigned int base_mhz = ecx & 0xFF;
    return base_mhz * 1000000;
}

/// @brief gets all logical processors (threads)
/// @return int threads
unsigned int amd_cpu_get_logical_processor_count(){
    unsigned int eax, ebx, ecx, edx;
    cpuid(0x80000008, 0, &eax, &ebx, &ecx, &edx);

    return (ecx & 0xFF) + 1;
}
