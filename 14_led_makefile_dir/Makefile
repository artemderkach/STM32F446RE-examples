# $@ - target
# $^ - prerequisite

OBJDIR := build

SRCS = main.c startup_stm32f446xx.S

# [main.c some.s] -> [main.o some.o]
OBJS := $(SRCS:.c=.o)
OBJS := $(OBJS:.s=.o)
OBJS := $(OBJS:.S=.o)

OBJS := $(addprefix $(OBJDIR)/, $(OBJS))

CC = arm-none-eabi-gcc
CFLAGS =

LDFLAGS = -nostartfiles
LDFLAGS += -TSTM32F446RETx.ld

# Machine-Dependent Options (ARM)
MDFLAGS = -mthumb

all: $(OBJS)
	$(CC) $(LDFLAGS) -o $(OBJDIR)/main.elf $^

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(MDFLAGS) -c -o $@ $^

$(OBJDIR)/%.o: %.s | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $^

$(OBJDIR)/%.o: %.S | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $^

$(OBJDIR):
	mkdir -p $@

flash:
	openocd -f board/st_nucleo_f4.cfg -c "program build/main.elf verify reset exit"

clean:
	rm -f $(OBJDIR)

print-%: ; @echo $* = $($*)