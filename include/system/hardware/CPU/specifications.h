#ifndef _SPECIFICATIONS_H
#define _SPECIFICATIONS_H   1

unsigned int amd_cpu_get_physical_core_count();
unsigned int amd_cpu_get_thread_per_core();
unsigned int amd_cpu_get_logical_processor_count();

unsigned int intel_cpu_get_logical_processor_count();
unsigned int intel_cpu_get_thread_count();
unsigned int intel_cpu_get_physical_core_count();

int get_physical_cores();

#endif
