#include <stdio.h>
#include <string.h>

#include <main.h>
#include <utils/arguments.h>
#include <utils/terminal.h>
#include <utils/asciiart.h>
#include <system/hardware/CPU/cpu.h>
#include <system/hardware/CPU/intel/processors.h>
#include <system/hardware/CPU/microarch.h>
#include <system/hardware/CPU/specifications.h>

/// @brief Spec Seek Entry Point
/// @param argc argument count
/// @param argv argument vector

int main(int argc, const char** argv){
    if (construct_arguments(argc, argv) != 0) return -1;
    if (!get_arguments().no_ansi) CLEAR_SCREEN();
    
    if (get_arguments().help){
        print_help(); return 0;
    }
    
    ASCII_DIVIDER("Spec Seek by Mellurboo", BLUE);
    printf("%sCompiled with GCC Version %d.%d.%d\n", BLUE,__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    printf("%sCompiled at: %s : %s\n", BLUE, __DATE__, __TIME__);

    cpu_info(init_cpu());

    // Windows will close straight away after execution so this allows users to read it.
    #if defined(_WIN32)
    printf("\n%sSpec Seek has finished, Press any key to exit: ", BWHITE);
    getchar();
    #endif

    printf("%s", RESET);
    fflush(stdout);
}

/// @brief Print and Display the CPU information
/// @param cpu populated cpu structure
void cpu_info(cpu_t cpu){
    IF_VERBOSE(2){
        ASCII_DIVIDER("CPUID", BOLD_VENDOR_COLOUR);
        printf("%sMax Supported CPUID Standard Leaf: %s0x%X\n", BWHITE, VENDOR_COLOUR, cpu_get_max_supported_leaf());
        printf("%sMax Supported CPUID Extended Leaf: %s0x%X", BWHITE, VENDOR_COLOUR, cpu_get_max_supported_extended_leaf());
    }

    ASCII_DIVIDER("Processor", BOLD_VENDOR_COLOUR);
    printf("%sName:      %s%s\n", BWHITE, VENDOR_COLOUR, cpu.name);
    IF_VENDOR_AMD({printf("%sMicroarch: %s%s\n", BWHITE, VENDOR_COLOUR, amd_cpu_get_microarch(cpu.family, cpu.model, cpu.ext_model));});
    IF_VENDOR_INTEL({printf("%sMicroarch: %s%s\n", BWHITE, VENDOR_COLOUR, intel_get_cpu_microarch(cpu.family, cpu.base_model, cpu.ext_model, cpu.revision));});
    printf("%sVendor:    %s%s\n", BWHITE, VENDOR_COLOUR, cpu.vendor);
    ASCII_DIVIDER_SMALL("Identifiers", BOLD_VENDOR_COLOUR);
    printf("%sModel: %s0x%X:\n", BWHITE, VENDOR_COLOUR, cpu.model);
    printf("  %sBase Model: %s0x%X\n", BWHITE, VENDOR_COLOUR, cpu.base_model);
    printf("  %sExt. Model: %s0x%X\n", BWHITE, VENDOR_COLOUR, cpu.ext_model);
    printf("%sFamily:\t%s0x%X:\n", BWHITE, VENDOR_COLOUR, cpu.family);
    printf("  %sBase Family: %s0x%X\n", BWHITE, VENDOR_COLOUR, cpu.base_family);
    printf("  %sExt. Family: %s0x%X\n", BWHITE, VENDOR_COLOUR, cpu.ext_family);
    printf("%sRevision: %s0x%X", BWHITE, VENDOR_COLOUR, cpu.revision);
    ASCII_DIVIDER_SMALL("Specifications", BOLD_VENDOR_COLOUR);
    printf("%sLogical Processors: %s%u\n", BWHITE, VENDOR_COLOUR, cpu.logical_processors);
    printf("%sPhysical Cores:  %s%u\n", BWHITE, VENDOR_COLOUR, cpu.physical_processors);
    printf("%sThreads PerCore: %s%u\n", BWHITE, VENDOR_COLOUR, cpu.threads_per_core);
    // handle intels weird core archetectures.
    IF_VENDOR_INTEL({
        if (cpu_supports_standard_leaf(0x0000001A)){
            printf("  %sPerformance Cores: %s%u\n", BWHITE, VENDOR_COLOUR, cpu.performance_cores);
            printf("  %sEfficiency Cores: %s%u\n", BWHITE, VENDOR_COLOUR, cpu.efficient_cores);
        }
    });

    /*
        Printing the CPU features (Platform Specific logic is handled within the functions below.)
    */
    ASCII_DIVIDER("CPU Standard Features", BYELLOW);
    cpu_check_standard_features();
    ASCII_DIVIDER("CPU Extended Features", BYELLOW);
    cpu_check_extended_features();
    printf("\n");
}
