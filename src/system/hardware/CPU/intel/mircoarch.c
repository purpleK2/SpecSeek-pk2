#include <system/hardware/CPU/microarch.h>

/// @brief get the Micro archetecture for the Current CPU [INTEL ONLY]
/// @param family CPU Family Value
/// @param base_model the CPUs BASE model
/// @param ext_model the CPUs Extended Model
/// @param stepping revision?
/// @return Microarchetecture string.
const char* intel_cpu_get_microarch(unsigned int family,
    unsigned int base_model,
    unsigned int ext_model,
    unsigned int stepping){
    switch (family){
        case 0x4:
            return "Intel 486";
        case 0x5:
            switch (base_model){
                case 0x01 ... 0x08:
                    return "P5";
                case 0x09 ... 0x0A:
                    return "Lakemont";
                default:
                    break;
            }
            break;
        case 0x6:
            switch (base_model){
                case 0x5:
                    switch(ext_model){
                        case 0x0:
                            return "P6";
                        case 0x1:
                            return "Pentium M";
                        case 0x2:
                            return "Westmere";
                        case 0x4:
                            return "Haswell";
                        case 0x5:
                            switch (stepping){
                                case 0x0:
                                    return "Skylake";
                                case 0x5 ... 0x07:
                                    return "Cascade Lake";
                                case 0x11:
                                    return "Cooper Lake";
                                default:
                                    return "Unknown Intel Processor";
                            }
                        case 0xA:
                            return "Comet Lake";
                        case 0xB:
                        case 0xC:
                            return "Arrow Lake";
                        default:
                            return "Unknown Intel Processor";
                    }    
                    break;
                case 0x6:
                    switch (ext_model){
                        case 0x1:
                            return "Core";
                        case 0x4:
                            return "Haswell";
                        case 0x5:
                            return "Broadwell (EP+)";
                        case 0x6:
                            return "Cannon Lake";
                        case 0xA:
                            return "Comet Lake";
                        case 0xC:
                            return "ARrow Lake";
                        default:
                            return "Unknown Intel Processor";
                            break;
                    }
                case 0x7:
                    switch (ext_model){
                        case 0x1:
                            return "Penryn";
                        case 0x4:
                            return "Broadwell";
                        case 0x9:
                            return "Alder Lake";
                        case 0xA:
                            return "Rocket Lake";
                        case 0xB:
                            return "Raptor Lake or Barlett Lake";
                        default:
                            return "Unknown Intel Processor";
                            break;
                    }
                case 0xA:
                    switch (ext_model){
                        case 0x0:
                            return "P6";
                        case 0x1:
                            return "Nehalem";
                        case 0x2:
                            return "Sandy Bridge";
                        case 0x3:
                            return "Ivy Bridge";
                        case 0x6:
                            return "Ice Lake";
                        case 0x9:
                            return "Alder Lake";
                        case 0xA:
                            return "Meteor Lake";
                        case 0xB:
                            return "Raptor Lake or Barlett Lake";
                        default:
                            return "Unknown Intel Processor";
                            break;
                    }
                    break;
                case 0xB:
                    switch (ext_model){
                        case 0x0:
                            return "P6";
                        case 0xA:
                            return "Meteor Lake";
                        default:
                            return "Unknown Intel Processor";
                            break;
                    }
                    break;
                case 0x9:
                case 0xC:
                    switch (ext_model){
                        case 0x3:
                            return "Haswell";
                        case 0x2:
                            return "Westmere";
                        case 0x6:
                            return "Ice Lake";
                        case 0x8:
                            return "Tiger Lake";
                        case 0xA:
                            return "Meteor Lake";
                        case 0xB:
                            return "Lunar Lake";
                        case 0xC:
                            return "Panther Lake";
                        default:
                            return "Unknown Intel Processor";
                            break;
                    }
                    break;
                case 0xD:
                    switch (ext_model){
                        case 0x0:
                            return "Modified Pentium M";
                        case 0x1:
                            return "Penryn";
                        case 0x2:
                            return "Sandy Bridge";
                        case 0x3:
                            return "Broadwell";
                        case 0x7:
                            return "Ice Lake";
                        case 0x8:
                            return "Tiger Lake";
                        case 0xA:
                            return "Granite Rapids";
                        case 0xB:
                            return "Lunar Lake";
                        case 0xC:
                            return "Wildcat Lake";
                        case 0xD:
                            return "Clearwater Forest";
                        default:
                            return "Unknown Intel Processor";
                            break;
                    }
                    break;
                case 0xE:
                    switch (ext_model){
                        case 0x0:
                            return "Modified Pentium M";
                        case 0x1:
                        case 0x2:
                            return "Nehalem";
                        case 0x3:
                            return "Ivy Bridge";
                        case 0x4:
                        case 0x5:
                            return "Skylake";
                        case 0x7:
                            return "Ice Lake";
                        case 0x8:
                            switch (stepping){
                                case 0x9:
                                    return "Amber Lake";
                                case 0x10:
                                    return "Coffee Lake";
                                case 0x11:
                                case 0x12:
                                    return "Whiskey Lake";
                                default:
                                    return "Kaby Lake"; 
                            }
                        case 0x9:
                            return "Kaby Lake or Coffee Lake";
                        case 0xA:
                            return "Granite Rapids";
                        case 0xB:
                            return "Raptor Lake or Barlett Lake";
                        default:
                            return "Unknown Intel Processor";
                            break;
                    }
                    break;
                case 0xF:
                    switch (ext_model){
                        case 0x0:
                            return "Core";
                        case 0x1:
                            return "Nehalem";
                        case 0x2:
                            return "Westmere";
                        case 0x3:
                            return "Haswell";
                        case 0x4:
                            return "Broadwell";
                        case 0x8:
                            return "Sapphire Rapids";
                        case 0xA:
                            return "Sierra Forest";
                        case 0xC:
                            return "Emerald Rapids";
                        case 0xB:
                            return "Raptor Lake or Barlett Lake";
                        default:
                            return "Unknown Intel Processor";
                            break;
                    }
                    break;
                default:
                    return "Unknown Intel Processor";
                    break;
            }
            break;
        case 0xF:
            switch (base_model){
                case 0x1 ... 0x4:
                    return "Netburst";
                case 0x6:
                    return "Modified Pentium M";
                default:
                    return "Unknown Intel Processor";
                    break;
            }
            break;
        default:
            return "Unknown Intel Microarch";
    }
    return "Unknown Intel Microarch";
}