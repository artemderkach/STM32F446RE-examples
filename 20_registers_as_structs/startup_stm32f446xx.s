// Vector table
.section  .isr_vector, "a"

	.word    _estack    // Top of the stack. from linker script
	.word    main +1    // ref to ResetHandler function. +1 for thumb mode
