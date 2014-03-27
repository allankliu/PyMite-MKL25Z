#https://github.com/payne92/bare-metal-arm/blob/master/Makefile

#GCCBIN = D:/maple-ide-0.0.12-windowsxp32/hardware/tools/arm/bin
#GCCBIN = C:/gcc-arm/gcc-arm-none-eabi-4_7-2013q1-20130313-win32/bin
GCCBIN = C:/gcc-arm-none-eabi-4_7-2013q1-20130313-win32/bin
CC = $(GCCBIN)/arm-none-eabi-gcc
AR = $(GCCBIN)/arm-none-eabi-ar
OBJCOPY = $(GCCBIN)/arm-none-eabi-objcopy
OBJDUMP = $(GCCBIN)/arm-none-eabi-objdump
SIZE = $(GCCBIN)/arm-none-eabi-size
RM = rm

DEBUG_OPTS = -g3 -gdwarf-2
OPTS = -Os
TARGET_CPU = -mcpu=cortex-m0
CFLAGS = -ffunction-sections -fdata-sections -Wall -Wa,-adhlns=$(addsuffix .lst, $(basename $<)) \
		 -fmessage-length=0 $(TARGET_CPU) -mthumb -mfloat-abi=soft \
		 $(DEBUG_OPTS) $(OPTS) -I .


LIBOBJS = _startup.o syscalls.o uart.o delay.o accel.o touch.o usb.o \
		ring.o tests.o systick.o
#LIBOBJS = _startup.o syscalls.o uart.o delay.o accel.o touch.o usb.o ring.o

INCLUDES = freedom.h common.h

.phony: clean gcc-arm

#all: demo.srec demo.dump
#all: demo.dump demo.srec
all: demo.elf demo.srec demo.hex demo.bin

libbare.a: $(LIBOBJS)
	$(AR) -rv libbare.a $(LIBOBJS)
	
clean:
	$(RM) *.o *.lst *.elf libbare.a *.srec *.hex *.bin
#	$(RM) *.o *.lst *.out libbare.a *.srec *.dump

%.o: %.c
	$(CC) $(CFLAGS) -c $<
	
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

gcc-arm: