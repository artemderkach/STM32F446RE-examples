MEMORY {
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K  /* 0x0808.0000 */
	SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K  /* 0x2002.0000 */
}

SECTIONS {
	.text ORIGIN(FLASH) : {
		*(.text)
	}
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);