build:
	arm-none-eabi-gcc -mcpu=cortex-m4 -c -o main.o main.s
	arm-none-eabi-gcc -Wl,--gc-sections -TSTM32F446RETx.ld -o main.elf main.o