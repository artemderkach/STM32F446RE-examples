# STM32F446RE
- [1_led_minimal_asm](#1_led_minimal_asm)
- [2_blinky_minimal_asm](#2_blinky_minimal_asm)
- [3_led_minimal](#3_led_minimal)

## 1_led_minimal_asm
Minimal representation of turning on LED using assembler
- `main.s`
- `.ld` - linker

## 2_blinky_minimal_asm (in progress)
Same as `1_led_minimal_asm` but LED is blinking.

## 3_led_minimal
Same as `1_led_minimal_asm` but logic from `.s` file moved to `.c ` and `.s` is now startup file
- `main.c`
- `.s` - startup
- `.ld` - linker