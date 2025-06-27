#define _GNU_SOURCE

#include <system/hardware/CPU/cpu.h>
#include <system/hardware/CPU/specifications.h>
#include <system/hardware/CPU/intel/processors.h>
#include <system/hardware/CPU/affinity.h>
#include <utils/terminal.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int efficient_core_count = 0;
unsigned int performance_core_count = 0;

/// @brief gets the ammount of CPU threads per Physical Core
/// @return unsigned int threads per core
unsigned int intel_cpu_get_threads_per_core(){
    return 0;
}

/// @brief INTEL ONLY Gets the logical processor count for the CPU Package
/// @return Logicial Processor Count
unsigned int intel_cpu_get_logical_processor_count(void) {
    unsigned int eax, ebx, ecx, edx;

    unsigned int count = 0;
    unsigned int leaf = (cpu_get_max_supported_leaf() >= 0x1F) ? 0x1F : 0x0B;

    for (unsigned int level = 0; level < 32; ++level) {
        cpuid(leaf, level, &eax, &ebx, &ecx, &edx);

        unsigned int level_type = (ecx >> 8) & 0xFF;
        if (level_type == 0 || ebx == 0)
            break;

        count = (ebx > count) ? ebx : count; // get the max number of logical processors at any level
    }
    return count;
}

/// @brief gets the type of hybrid core it is, only should be run on CPUs that support 1Ah
/// @return 1 (e-core) 2 (p-core)
unsigned int intel_cpu_get_hybrid_core_type(void){
    if (!cpu_supports_standard_leaf(0x0000001A)) {
        printf("%s%s:%d Hybrid function not supported on non hybrid CPU\nThis is an Error, please report at https://github.com/Mellurboo/SpecSeek", BRED, __FILE__, __LINE__);
        return 0;
    }
    unsigned int eax, ebx, ecx, edx;
    cpuid(0x1A, 0, &eax, &ebx, &ecx, &edx);

    unsigned int core_type = (eax >> 24) & 0xFF;
    return core_type;
}

/// @brief gets the APIC ID of the Intel CPU to differenciate between physical cores
/// @param VOID
/// @return apic id
unsigned int intel_cpu_get_apic_id(void){
    unsigned int eax, ebx, ecx, edx;
    cpuid(0x0000000B, 1, &eax, &ebx, &ecx, &edx);
    return edx;
}

/// @brief SMT (bit width) for CPU physical cores and threads
/// @param VOID
/// @return SMT Bit witdth
unsigned int intel_cpu_get_smt_mask_width(void) {
    unsigned int eax, ebx, ecx, edx;
    unsigned int smt_width = 0;

    // Loop levels to find SMT width
    for (unsigned int level = 0; level < 5; level++) {
        cpuid(0x0B, level, &eax, &ebx, &ecx, &edx);
        unsigned int level_type = (ecx >> 8) & 0xFF;
        if (level_type == 1) {
            smt_width = eax & 0x1F; // EAX[4:0] = bit width
            break;
        }
    }

    return smt_width;
}

/// @brief gets the physical core count of the intel CPU
/// @param VOID
/// @return unsigned int core count
unsigned int intel_cpu_get_physical_core_count(void) {
    unsigned int eax, ebx, ecx, edx;

    if (cpu_get_max_supported_leaf() >= 0x0000001F){
        unsigned int total_cores = 0;
        unsigned int processors = intel_cpu_get_logical_processor_count();
        core_apic_t *cores = malloc(sizeof(core_apic_t) * processors);

        for(unsigned int i = 0; i < processors; i++){
            if (cpu_set_affinity(i) != 0){
                printf("%s%s:%d SpecSeek failed to set affinity on pass %d\nThis is an Error, please report at https://github.com/Mellurboo/SpecSeek", BRED, __FILE__, __LINE__, i);
                continue;   // this will mean we can see if they all fail or not? which might be helpful later.
            }
            
            unsigned int apic_id = intel_cpu_get_apic_id();
            unsigned int core_type = intel_cpu_get_hybrid_core_type();
            unsigned int core_id = apic_id >> intel_cpu_get_smt_mask_width();

            int found = 0;
            for (unsigned int j = 0; j < total_cores; j++) {
                if (cores[j].apic_id == core_id) {
                    found = 1;
                    break;
                }
            }

            if (!found) {
                cores[total_cores].apic_id = core_id;
                cores[total_cores].core_type = core_type;
                total_cores++;
            }
        }

        // determine what kinda cores we have
        for (unsigned int i = 0; i < total_cores; i++){
            if (cores[i].core_type == 0x20) efficient_core_count++;
            if (cores[i].core_type == 0x40) performance_core_count++;
        }

        free(cores);
        return performance_core_count + efficient_core_count;

    }else if (cpu_get_max_supported_leaf() >= 0x0000000B){;
        unsigned int smt_mask_width = 0;
        unsigned int core_mask_width = 0;

        for (unsigned int level = 0; level < 5; ++level) {
            cpuid(0x0B, level, &eax, &ebx, &ecx, &edx);

            unsigned int level_type = (ecx >> 8) & 0xFF;
            if (level_type == 0 || ebx == 0)
                break;

            printf("Level %u: EAX=0x%x EBX=%u ECX=0x%x (level_type=%u)\n",
                level, eax, ebx, ecx, level_type);

            if (level_type == 1) {  // SMT level
                smt_mask_width = eax & 0x1F;
                printf("SMT mask width = %u\n", smt_mask_width);
            } else if (level_type == 2) {  // Core level
                core_mask_width = eax & 0x1F;
                printf("Core mask width = %u\n", core_mask_width);
            }
        }

        unsigned int logical_processors = intel_cpu_get_logical_processor_count();
        printf("Logical processors = %u\n", logical_processors);

        if (core_mask_width == 0) {
            printf("Core mask width is zero, cannot compute physical cores.\n");
            return 0;
        }

        if (core_mask_width <= smt_mask_width) {
            printf("Core mask width (%u) <= SMT mask width (%u), invalid data.\n",
                   core_mask_width, smt_mask_width);
            return 0;
        }

        unsigned int threads_per_core = 1U << (core_mask_width - smt_mask_width);
        printf("Threads per core = %u\n", threads_per_core);

        unsigned int physical_cores = logical_processors / threads_per_core;
        printf("Physical cores computed = %u\n", physical_cores);

        return physical_cores;
    }

    return 0;
}

/// @brief helper function to return the ammount of performance cores on a hybrid CPU
/// @param  VOID
/// @return unsigned int performance cores
unsigned int intel_cpu_get_performance_core_count(void){
    return performance_core_count;
}

/// @brief helper function to return the ammount of efficent cores on a hybrid CPU
/// @param  VOID
/// @return unsigned in efficent cores
unsigned int intel_cpu_get_efficient_core_count(void){
    return efficient_core_count;
}