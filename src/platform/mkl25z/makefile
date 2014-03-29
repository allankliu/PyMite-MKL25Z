#https://github.com/payne92/bare-metal-arm/blob/master/Makefile

# The makefile comes from bare-metal-arm, merged with AVR-GCC makefile from PyMite.
# - Allan K Liu


# PyMite Configuration
PLATFORM := $(notdir $(CURDIR))
PM_LIB_ROOT := pmvm_$(PLATFORM)
PM_LIB_FN = lib$(PM_LIB_ROOT).a
PM_LIB_PATH = ../../vm/$(PM_LIB_FN)
PM_USR_SOURCES = main.py
PMIMGCREATOR := ../../tools/pmImgCreator.py
PMGENPMFEATURES := ../../tools/pmGenPmFeatures.py
IPM=false

# Platform Configuration
MCU = cortex-m0
TARGET = main
SRC = $(TARGET).c plat.c $(TARGET)_nat.c $(TARGET)_img.c
ASRC =
OPT = s

# Debugging format.
# Original for cortex-m0
#DEBUG_OPTS = -g3 -gdwarf-2
DEBUG_OPTS = stabs

# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD = -std=gnu99

OPTS = -Os
CFLAGS = -ffunction-sections -fdata-sections -Wall -Wa,-adhlns=$(addsuffix .lst, $(basename $<)) \
		 -fmessage-length=0 -mcpu=$(MCU) -mthumb -mfloat-abi=soft \
		 -g$(DEBUG_OPTS) $(OPTS) -I .

# PyMite CDEFS
ifeq ($(DEBUG), true)
	CDEFS += -g -g$(DEBUG_OPTS) -D__DEBUG__=1
endif

# Place -I options here
CINCS = -I../../vm -I$(abspath .)
CFLAGS += $(CDEFS) $(CINCS)


LIBOBJS = _startup.o syscalls.o uart.o delay.o accel.o touch.o usb.o \
		ring.o tests.o systick.o plat.o
#LIBOBJS = _startup.o syscalls.o uart.o delay.o accel.o touch.o usb.o ring.o

INCLUDES = freedom.h common.h

# PyMite: tell the compiler where to find pm.h and libpmvm_<plat>.a
CFLAGS += -I../../
LDFLAGS += -L../../vm -lpmvm_<plat>

# Toolchain
GCCBIN = C:/gcc-arm-none-eabi-4_7-2013q1-20130313-win32/bin
SHELL = sh
CC = $(GCCBIN)/arm-none-eabi-gcc
OBJCOPY = $(GCCBIN)/arm-none-eabi-objcopy
OBJDUMP = $(GCCBIN)/arm-none-eabi-objdump
SIZE = $(GCCBIN)/arm-none-eabi-size
AR = $(GCCBIN)/arm-none-eabi-ar
NM = $(GCCBIN)/arm-none-eabi-nm
RM = rm -f
MV = mv -f
COPY = cp

# Define all object files.
OBJ = $(SRC:.c=.o) $(ASRC:.S=.o)

# Define all listing files.
LST = $(ASRC:.S=.lst) $(SRC:.c=.lst)

# Default target.
#all: demo.srec demo.dump
#all: demo.dump demo.srec
all: pmfeatures.h pmvm build

build: elf srec hex bin

elf: $(TARGET).elf

srec: $(TARGET).srec
hex: $(TARGET).hex
bin: $(TARGET).bin

libbare.a: $(LIBOBJS)
	$(AR) -rv libbare.a $(LIBOBJS)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $<
	
pmfeatures.h: pmfeatures.py $(PMGENPMFEATURES)	
	$(PMGENPMFEATURES) pmfeatures.py > $@

# PyMite: Build the VM archive if it doesn't exist
pmvm : $(PM_LIB_PATH)

$(PM_LIB_PATH) : ../../vm/*.c ../../vm/*.h
	make -C ../../vm

# PyMite: Generate native code and module images from the python source
$(TARGET)_nat.c $(TARGET)_img.c : $(PM_USR_SOURCES)
	$(PMIMGCREATOR) -f pmfeatures.py -c -u -o $(TARGET)_img.c --native-file=$(TARGET)_nat.c $(PM_USR_SOURCES)


%.dump: %.elf
	$(SIZE) $<
	$(OBJDUMP) --disassemble $< >$@
	
%.srec: %.elf
	$(OBJCOPY) -O srec $< $@
	$(SIZE) $@

%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@
	$(SIZE) $@
	
%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

#%.out: %.o mkl25z4.ld libbare.a
#	$(CC) $(CFLAGS) -T mkl25z4.ld -o $@ $< libbare.a

%.elf: %.o mkl25z4.ld libbare.a
	$(CC) $(CFLAGS) -T mkl25z4.ld -o $@ $< libbare.a

# Target: clean project.
clean:
	$(MAKE) -C ../../vm clean
	$(RM) *.o *.lst *.elf libbare.a *.srec *.hex *.bin
	$(RM) $(TARGET)_img.*
	$(RM) $(TARGET)_nat.*
	$(RM) pmfeatures.h

depend:
	if grep '^# DO NOT DELETE' $(MAKEFILE) >/dev/null; \
	then \
		sed -e '/^# DO NOT DELETE/,$$d' $(MAKEFILE) > \
			$(MAKEFILE).$$$$ && \
		$(MV) $(MAKEFILE).$$$$ $(MAKEFILE); \
	fi
	echo '# DO NOT DELETE THIS LINE -- make depend depends on it.' \
		>> $(MAKEFILE); \
	$(CC) -M -mmcu=$(MCU) $(CDEFS) $(CINCS) $(SRC) $(ASRC) >> $(MAKEFILE)


# PyMite: Append pmvm to the list of .PHONY targets
.PHONY: all build elf hex clean depend pmvm

# PyMite: Export these env variables so the Makefile in ../../vm gets them
export CC OBJCOPY NM CFLAGS ALL_CFLAGS AR IPM PM_LIB_FN
