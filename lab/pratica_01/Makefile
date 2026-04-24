CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS = -mcpu=cortex-a8 -O2 -g -Wall -Iinc
LDFLAGS = -T src/memmap.ld

SRCS = src/startup.s \
src/main.c

OBJS = $(addprefix obj/, $(notdir $(SRCS:.c=.o)))
OBJS := $(OBJS:.s=.o)

TARGET = bin/app_baremetal

all: $(TARGET).bin copy

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/%.s
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

copy:
	cp bin/app_baremetal.bin /srv/tftpboot/

clean:
	rm -f obj/*.o bin/*.dump bin/*.elf bin/*.bin