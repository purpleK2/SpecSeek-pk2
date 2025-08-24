
![Logo](https://i.imgur.com/Zg37VpH.png)
# SpecSeek. All in One Specification Tool

A soloution to finding everything there is to know about a computers specifications. all in one elegant location. **a great way to share your device specifications support and features**. not sure if your PC supports some functionality? SpecSeek will relay that to you.

## Contributing
Contributions in any way are always welcome, if its porting to your own operating system or making a PR for me to review, I welcome all sorts of contributions and intergration. when porting I would appreciate it if your build script pulls directly from this repo to keep your build of specseek up to date as its still in active development.

**When contributing please try follow the naming standard used already, and do not add repeat functionality. please keep a simple codebase as a priority.**
## Build & Run from Source
to build the ELF executables use the following command
``` bash
make
```
however to create the Windows Executables use the following command
``` bash
make windows
```

The makefile supports arguments like `CC` for your own GCC toolchain and `CFLAGS` to define compiler flags (they are appended with COMMON_FLAGS which you must change in the makefile. CFLAGS is simply adding flags)

## Exsisting Ports:
Check out some of the exsisting ports for specseek;\
    [MinOS by Dcraft BG](https://github.com/Mellurboo/MinOS_SpecSeek)\
    [TacOS by UnmappedStack](https://github.com/UnmappedStack/SpecSeek-forTacOS)\
    [BananOS by Bananymous](https://github.com/Bananymous/banan-os)\
    [Stanix by Tayoky](https://github.com/tayoky/ports/blob/main/ports/specseek/specseek.ini)\
Thanks to everyone who puts time into porting or contributing to specseek. I love seeing it all!

## Minimum Requirements
Currently your CPU must be at least 32-bit and have the CPUID instruction.

- AMD-K5 processor models 1, 2, 3
- Intel SL-Enhanced 486


## Appendix
SpecSeek is built as a soloution to the problem of people not knowing their hardware specs, which makes the lives of technitions harder. However specseek has grown within the community of OSDev, as a result keeping the code simple and portable is going to be and remain a number 1 priority.

also sorry for the inconsistancy of how I comment, sometimes I feel /// is appropriate usually for the top of functions, sometimes I use // for comments in the function, if im writing a block of text ill use /* */ but sometimes I might use them interchangably. Feel free to change them.
