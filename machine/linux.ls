ENTRY(get_protected) 

SECTIONS 
{
    . = 0x100000;     /* Startadresse des Systems */

    .init :
    {
        *(.init)
        *(.initdata)
    }

    .text BLOCK(4K): ALIGN(4K)
    {
        *(.text.hot .text.hot.*)
        *(".text")
        *(".text$")
        *(.text .text.* .gnu.linkonce.t.*)
    }

    .rodata :
    {
        *(.rodata .rodata.* .gnu.linkonce.r.*)
    }

    .init_array :
    {
        PROVIDE (start_ctors = .);
        KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*)));
        KEEP(*(.init_array));
        KEEP(*(SORT_BY_INIT_PRIORITY(.ctors.*)));
        KEEP(*(.ctors));
        PROVIDE(end_ctors = .);
    }

    .fini_array :
    {
        PROVIDE (start_dtors = .);
        KEEP(*(.fini_array.*));
        KEEP(*(.fini_array));
        KEEP(*(.dtors.*));
        KEEP(*(.dtors));
        PROVIDE(end_dtors = .);
    }

    .data :
    {
        *(.data .data.* .gnu.linkonce.d.*)
    }

    .bss : 
    {
        *(.bss .bss.* .gnu.linkonce.b.*)
    }

    .paging : ALIGN(4K)
    {
        *(".paging")
    }

    /DISCARD/ :
    {
        *(".note")
        *(".comment")
        *(".note.GNU-stack")
    }
}

