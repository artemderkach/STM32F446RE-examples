all:
	mkdir -p build
	arm-none-eabi-gcc -mcpu=cortex-m4 -c -o build/main.o main.s
	arm-none-eabi-gcc -nostartfiles -TSTM32F446RETx.ld -o build/main.elf build/main.o

clean:
	rm -rf build

flash:
	openocd -f board/st_nucleo_f4.cfg -c "program build/main.elf verify reset exit"