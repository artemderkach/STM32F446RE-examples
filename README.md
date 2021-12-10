This repo is reflecting the learning process of embedded programming.
Examples are listed with incremental complexity, next one adds new element to existing.

## Common Flags Description
- `-nostartfiles` - Do not use the standard system startup files when linking


# STM32F446RE
- [01_asm_led_minimal](#01_asm_led_minimal)
- [02_asm_led_constants](#02_asm_led_constants)
- [03_asm_led_ram](#03_asm_led_ram)
- [11_led_minimal](#11_led_minimal)
- [12_led_minimal_constants](#12_led_minimal_constants)
- [13_led_minimal_makefile](#13_led_minimal_makefile)

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
 
## 12_led_minimal_constants
Same as `11_led_minimal` but `#define` is used for variables

## 13_led_minimal_makefile
Same as `12_led_minimal_constants` but `Makefile` is now fancy
