SRCS = main.c startup_stm32f446xx.S

# [main.c some.s] -> [main.o some.o]
OBJS := $(SRCS:.c=.o)
OBJS := $(OBJS:.s=.o)
OBJS := $(OBJS:.S=.o)

CC = arm-none-eabi-gcc
CFLAGS = -Wall

LDFLAGS = -Wl,--gc-sections -nodefaultlibs --specs=nano.specs
LDFLAGS += -TSTM32F446RETx_FLASH.ld

# Machine-Dependent Options (ARM)
MDFLAGS = -mlittle-endian -mthumb -mcpu=cortex-m4 -march=armv7e-m -mfloat-abi=hard -mfpu=fpv4-sp-d16

target = blinky.elf

target: $(OBJS)
	$(CC) -o blinky.elf $^ $(MDFLAGS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(MDFLAGS) -c -o $@ $^

%.o: %.s
	$(CC) $(CFLAGS) $(MDFLAGS) -c -o $@ $^

%.o: %.S
	$(CC) $(CFLAGS) $(MDFLAGS) -c -o $@ $^

clean:
	rm -f $(OBJS) $(target)

print-%: ; @echo $* = $($*)