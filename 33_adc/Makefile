# $@ - target
# $^ - prerequisite

TARGET := blinky
OBJDIR := build

SRCS = main.c startup_stm32f446xx.S

# [main.c some.s] -> [main.o some.o]
OBJS := $(SRCS:.c=.o)
OBJS := $(OBJS:.s=.o)
OBJS := $(OBJS:.S=.o)

OBJS := $(addprefix $(OBJDIR)/, $(OBJS))

CC = arm-none-eabi-gcc
CFLAGS =

ifeq ($(DEBUG), 1)
	CFLAGS += -g3 -gdwarf-2
endif

LDFLAGS = -nostartfiles -specs=nosys.specs -specs=nano.specs
LDFLAGS += -TSTM32F446RETx.ld

# Machine-Dependent Options (ARM)
MDFLAGS = -mthumb

all: $(OBJDIR)/$(TARGET).elf

$(OBJDIR)/$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(MDFLAGS) -c -o $@ $^

$(OBJDIR)/%.o: %.s | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $^

$(OBJDIR)/%.o: %.S | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $^

$(OBJDIR):
	mkdir -p $@

flash:
	openocd -f board/st_nucleo_f4.cfg -c "program build/blinky.elf verify reset exit"

clean:
	rm -f $(OBJDIR)

print-%: ; @echo $* = $($*)