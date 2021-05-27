SECTIONS
{
	. = 0x10000;     /* Startadresse des Systems */

	.text :
	{
		*(".startup")
		*(".init")
		*(".fini")
		*(".text")
		*(".text$*")
	}

	.data :
	{
		. = ALIGN(0x10);
		*(".data")
		*(".rdata$*")

		. = ALIGN(0x10);
		___CTOR_LIST__ = .;
		*(".ctors")
		___CTOR_LIST_END__ = .;

		. = ALIGN(0x10);
		___DTOR_LIST__ = .;
		*(".dtors")
		___DTOR_LIST_END__ = .;

	}

	.bss :
	{
		. = ALIGN(0x10);
		*(".bss")
	}
	/DISCARD/ :
	{
		*(".note")
		*(".comment")
	}
}
