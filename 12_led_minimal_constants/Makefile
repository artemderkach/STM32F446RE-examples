.PHONY: build
build:
	mkdir -p build
	arm-none-eabi-gcc -c -o build/startup_stm32f446xx.o startup_stm32f446xx.s
	arm-none-eabi-gcc -mthumb -c -o build/main.o main.c
	arm-none-eabi-gcc -nostartfiles -TSTM32F446RETx.ld -o build/main.elf build/main.o build/startup_stm32f446xx.o

clean:
	rm -rf build

flash:
	openocd -f board/st_nucleo_f4.cfg -c "program build/main.elf verify reset exit"