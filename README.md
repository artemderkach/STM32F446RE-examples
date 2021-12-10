This repo is reflecting the learning process of embedded programming.
Examples are listed with incremental complexity, next one adds new element to existing.

## Common Flags Description
- `-nostartfiles` - Do not use the standard system startup files when linking


# STM32F446RE
- [01_asm_led_minimal](#01_asm_led_minimal)
- [02_asm_led_constants](#02_asm_led_constants)
- [03_asm_led_ram](#03_asm_led_ram)
- [11_led_minimal](#11_led_minimal)
- [12_led_constants](#12_led_constants)
- [13_led_makefile](#13_led_makefile)
- [14_led_makefile_dir](#14_led_makefile_dir)

## 01_asm_led_minimal
Minimal representation of turning on LED using assembler
- `main.s`
- `.ld` - linker

## 02_asm_led_constants
Same as `01_asm_led_minimal` but constants are defined with `.equ`.

## 03_asm_led_ram
Same as `02_asm_led_constants` but `SRAM` added to linker file.

## 11_led_minimal
Same as `1_led_minimal_asm` but logic from `.s` moved to `.c ` and `.s` is now startup file
- `main.c`
- `.s` - startup
- `.ld` - linker

Added:
- `.isr_vector` section to separate from `.text`, otherwise no guarantee which is first
- `.isr_vector` section is allocatable due to `a` flag added
- `.c` file is compiled with `-mthumb`
 
## 12_led_constants
Same as `11_led_minimal` but `#define` is used for variables

## 13_led_makefile
Same as `12_led_constants` but `Makefile` is now fancy.<br>
```
OBJS := $(SRCS:.c=.o)
OBJS := $(OBJS:.s=.o)
OBJS := $(OBJS:.S=.o)
```
- Is used to replace target files to have `.o` extension. (`[main.c some.s] -> [main.o some.o]`)
- `$@` - target
- `$^` - prerequisite
- `print-%: ; @echo $* = $($*)` is used to print variable: `$ make print-OBJS` will give you list of objects.

## 14_led_makefile_dir
Same as `13_led_makefile` but `Makefile` is now creating build directory.<br>
- `OBJS := $(addprefix $(OBJDIR)/, $(OBJS))` pattern is used to add `build` in front of files
- `$(OBJDIR)/%.o` target also includes `build`
- `| $(OBJDIR)` to create directory only once
