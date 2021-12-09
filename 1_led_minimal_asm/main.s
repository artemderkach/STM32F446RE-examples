.thumb
.syntax unified

// RCC base                 0x4002.3800
// AHB1ENR register offset  0x0000.0030
.equ     RCC_AHB1ENR,   0x40023830

// GPIOA base address       0x4002.0000
// MODER register offset    0x0000.0000
// ODR   register offset    0x0000.0014
.equ     GPIOA_MODER,   0x40020000
.equ     GPIOA_ODR,     0x40020014


.section .text

// Vector table
	.word    _estack            // Top of the stack. from linker script
	.word    main +1            // +1 for thumb mode

main:
	// Enable GPIOA Peripheral Clock (bit 1 in AHB1ENR register)
	ldr r6, = RCC_AHB1ENR       // Load peripheral clock reg address to r6
	ldr r5, [r6]                // Read its content to r5
	orr r5, 0x00000001          // Set bit 1 to enable GPIOA clock
	str r5, [r6]                // Store result in peripheral clock register

	// Make GPIOA Pin5 as output pin (bits 11:10 in MODER register)
	ldr r6, = GPIOA_MODER       // Load GPIOA MODER register address to r6
	ldr r5, [r6]                // Read its content to r5
	and r5, 0xFFFFF3FF          // Clear bits 10, 11 for P5
	orr r5, 0x00000400          // Write 01 to bits 10, 11 for P5
	str r5, [r6]                // Store result in GPIOA MODER register

	// Set GPIOA Pin5 to 1 (bit 5 in ODR register)
	ldr r6, = GPIOA_ODR         // Load GPIOA output data register
	ldr r5, [r6]                // Read its content to r5
	orr r5, 0x0020              // write 1 to pin 5
	str r5, [r6]                // Store result in GPIOA output data register

