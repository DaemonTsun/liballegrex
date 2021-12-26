
ELFDUMP_TARGET  := psp-elfdump
ELFDUMP_SRC_FILES := mipsdisasm.c \
                     utils.c      \
                     elfdump.c

CC = gcc
LD = $(CC)
AR = ar

INCLUDES  = -I./ext

# Release flags
CFLAGS    = -Wall -Wextra -Wno-format-overflow -O2 -ffunction-sections -fdata-sections $(INCLUDES) $(DEFS) -MMD
LDFLAGS   = -s -Wl,--gc-sections
# Debug flags
#CFLAGS    = -Wall -Wextra -O0 -g $(INCLUDES) $(DEFS) -MMD
#LDFLAGS   =
LIBS      = -lcapstone

.PHONY: all clean default
default: all

all: $(ELFDUMP_TARGET)

$(ELFDUMP_TARGET): $(ELFDUMP_SRC_FILES)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ $(LIBS)

clean:
	rm -f $(ELFDUMP_TARGET)
