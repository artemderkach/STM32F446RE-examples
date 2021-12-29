.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

.global  g_pfnVectors
.global  Default_Handler

.word  _sidata // start address for the initialization values of the .data section. defined in linker script
.word  _sdata  // start address for the .data section. defined in linker script
.word  _edata  // end address for the .data section. defined in linker script
.word  _sbss   // start address for the .bss section. defined in linker script
.word  _ebss   // end address for the .bss section. defined in linker script
// stack used for SystemInit_ExtMemCtl; always internal RAM used


.section    .text.Reset_Handler
.weak       Reset_Handler
.type       Reset_Handler, %function

Reset_Handler:
    ldr     sp, =_estack // set stack pointer

    // Copy the data segment initializers from flash to SRAM
    ldr     r0, =_sdata
    ldr     r1, =_edata
    ldr     r2, =_sidata
    movs    r3, #0
    b       LoopCopyDataInit

CopyDataInit:
    ldr     r4, [r2, r3]
    str     r4, [r0, r3]
    adds    r3, r3, #4

LoopCopyDataInit:
    adds    r4, r0, r3
    cmp     r4, r1
    bcc     CopyDataInit

    // Zero fill the bss segment. */
    ldr     r2, =_sbss
    ldr     r4, =_ebss
    movs    r3, #0
    b       LoopFillZerobss

FillZerobss:
    str     r3, [r2]
    adds    r2, r2, #4

LoopFillZerobss:
    cmp     r2, r4
    bcc     FillZerobss

    bl      __libc_init_array // Call static constructors
    bl      main // Call the application's entry point.
    bx      lr

.size  Reset_Handler, .-Reset_Handler

.section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
    b  Infinite_Loop

    .size  Default_Handler, .-Default_Handler
    .section  .isr_vector,"a",%progbits
    .type  g_pfnVectors, %object
    .size  g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
