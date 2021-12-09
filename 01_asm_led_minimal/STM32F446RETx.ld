MEMORY {
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K  /* 0x0808.0000 */
}

SECTIONS {
	.text ORIGIN(FLASH) : {
		*(.text)
	}
}
