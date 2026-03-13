.PHONY: all clean distclean

include ../userspace.mk

TARGET = specseek
C_SRCS = $(shell find src -name '*.c')
OBJS = $(C_SRCS:.c=.o)

SYSROOT = $(USERSPACE_SYSROOT)
CFLAGS += -Iinclude -D_INTEL_AFFINITY=0
LDFLAGS = -nostdlib \
	-static \
	--entry=_start \
	-L$(SYSROOT)/usr/lib \
	$(SYSROOT)/usr/lib/Scrt1.o \
	$(SYSROOT)/usr/lib/crti.o \
	-lc \
	$(SYSROOT)/usr/lib/crtn.o \
	-o $(TARGET)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)

distclean: clean