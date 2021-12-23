MEMORY {
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K  /* 0x0808.0000 */
	SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K  /* 0x2002.0000 */
}

SECTIONS {
	.isr_vector : {
		*(.isr_vector)
	} > FLASH

	.text : {
	    *(.text)
	} > FLASH

  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = ALIGN(8);
  } >FLASH
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);
