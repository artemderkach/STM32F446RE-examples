This repo is reflecting the learning process of embedded programming.
Examples are listed with incremental complexity, next one adds new element to existing.

## Some Assembly Instructions
- `thumb` arm instruction set

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
- [15_blinky](#15_blinky)
- [16_blinky_seconds](#16_blinky_seconds)
- [20_registers_as_structs](#20_registers_as_structs)
- [21_external_defines](#21_external_defines)
- [22_external_defines_lib](#22_external_defines_lib)
- [23_bits](#23_bits)
- [30_gpio_input](#30_gpio_input)
- [31_uart](#31_uart)
- [32_uart_printf](#32_uart_printf)
- [33_adc](#33_adc)
- [34_pwm](#34_pwm)

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

## 15_blinky
Same as `14_led_makefile_dir` but LED is now blinking with some frequency.

## 16_blinky_seconds
Same as `15_blinky` but LED can be set to blink with frequency defined in seconds.

## 20_registers_as_structs
Same as `15_blinky` but registers is defined as structures. In a form of:
```
typedef struct {
    volatile uint32_t FIELD;
    ...
} REGISTER_typeDef;
```

## 21_external_defines
Same as `20_registers_as_structs` but register defines is taken form external lib `stm32f446xx.h`.
This file also got some dependencies. Overall files added:
- `cmsis_compiler.h`
- `cmsis_gcc.h`
- `cmsis_version.h`
- `core_cm4.h`
- `mpu_armv7.h`
- `stm32f446xx.h`
- `system_stm32f4xx.h`

## 22_external_defines_lib
Same as `21_external_defines` but external files is grouped in one folder. 
Requires updating include path in main file.

## 23_bits
Same as `22_external_defines_lib` its using bit registers. 

## 24_blinky_external
Blinky program but every register and constant is used form external library (`system_stm32f4xx.h`)

## 30_gpio_input
Get input from GPIO to manipulate LED.

## 31_uart
Steps to initialize UART:
1. GPIO:
   - Enable clock for GPIO
   - Select PIN to have alternate function
   - Select alternate function type
2. UART:
   - Enable clock for UART
   - Set value to BRR (Baud Rate Register)
   - Set UART module as output
   - Enable UART module
   
## 32_uart_printf
Add support for sending strings with `printf` function.
This requires more initializations in startup file + new sections is added to linker.
But it's not really reflect the minimal requirements for `printf` to work (will be figured later).

## 33_adc
Steps to initialize ADC:
1. GPIO:
   - Enable clock for GPIO
   - Select PIN to have analog function
2. ADC:
   - Enable clock for ADC
   - Set conversion sequence start
   - Set conversion sequence length
   - Enable ADC module

## 34_pwm
Steps to initialize ADC:
1. GPIO:
   - Enable clock for GPIO
   - Select PIN to have alternate function
   - Select alternate function type
2. PWM (TIM):
   - Enable clock for TIM
   - Set prescaler value (clock divider). freq = clock / prescaler
   - Set conversion sequence length
   - Enable ADC module
