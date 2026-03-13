.PHONY: all clean distclean

include ../userspace.mk

TARGET = specseek
C_SRCS = $(shell find src -name '*.c')
OBJS = $(C_SRCS:.c=.o)

CFLAGS += -Iinclude -D_INTEL_AFFINITY=0
LDFLAGS =

all: $(TARGET)

$(TARGET): $(OBJS)
	$(USERSPACE_LINK)

clean:
	rm -f $(OBJS) $(TARGET)

distclean: clean