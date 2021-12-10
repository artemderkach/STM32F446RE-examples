# $@ - target
# $^ - prerequisite

SRCS = main.c startup_stm32f446xx.S

# [main.c some.s] -> [main.o some.o]
OBJS := $(SRCS:.c=.o)
OBJS := $(OBJS:.s=.o)
OBJS := $(OBJS:.S=.o)

CC = arm-none-eabi-gcc
CFLAGS =

LDFLAGS = -nostartfiles
LDFLAGS += -TSTM32F446RETx.ld

# Machine-Dependent Options (ARM)
MDFLAGS = -mthumb

all: $(OBJS)
	$(CC) $(LDFLAGS) -o main.elf $^

%.o: %.c
	$(CC) $(CFLAGS) $(MDFLAGS) -c -o $@ $^

%.o: %.s
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $^

flash:
	openocd -f board/st_nucleo_f4.cfg -c "program main.elf verify reset exit"

clean:
	rm -f $(OBJS) main.elf

print-%: ; @echo $* = $($*)