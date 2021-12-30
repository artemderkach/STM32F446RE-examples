# $@ - target
# $^ - prerequisite

TARGET := adc
OBJDIR := build

SRCS = main.c startup_stm32f446xx.S
LDFILE = STM32F446RETx.ld

# [main.c some.s] -> [main.o some.o]
OBJS := $(SRCS:.c=.o)
OBJS := $(OBJS:.s=.o)
OBJS := $(OBJS:.S=.o)

OBJS := $(addprefix $(OBJDIR)/, $(OBJS))

CC = arm-none-eabi-gcc
CFLAGS = -Wall

ifeq ($(DEBUG), 1)
	CFLAGS += -g3 -gdwarf-2
endif

LDLIBS = -lc -lm -lnosys

LDFLAGS = -T$(LDFILE)
LDFLAGS += -specs=nano.specs -fdata-sections -ffunction-sections -Wl,--gc-sections

# Machine-Dependent Options (ARM)
MDFLAGS = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

all: $(OBJDIR)/$(TARGET).elf

$(OBJDIR)/$(TARGET).elf: $(OBJS)
	$(CC) $^ $(LDFLAGS) $(LDLIBS) $(MDFLAGS) -o $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(MDFLAGS) -c -o $@ $^

$(OBJDIR)/%.o: %.s | $(OBJDIR)
	$(CC) $(CFLAGS) $(MDFLAGS) -c -o $@ $^

$(OBJDIR)/%.o: %.S | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $^

$(OBJDIR):
	mkdir -p $@

flash:
	openocd -f board/st_nucleo_f4.cfg -c "program build/adc.elf verify reset exit"

clean:
	rm -f $(OBJDIR)

print-%: ; @echo $* = $($*)