ENTRY(_start)

MEMORY
{
    RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 128K
}

SECTIONS
{
    /* Código e inicialización */
    .text : {
        *(.text.startup)   /* punto de entrada */
        *(.text.init)      
        *(.text*)          /* resto del código */
    } > RAM

    /* Datos de solo lectura */
    .rodata : {
        *(.rodata*)
    } > RAM

    /* Variables inicializadas */
    .data : {
        _data_start = .;
        *(.data*)
        _data_end = .;
    } > RAM

    /* Variables no inicializadas (limpiadas en startup.s) */
    .bss : {
        _bss_start = .;
        *(.bss*)
        *(COMMON)
        _bss_end = .;
    } > RAM

    /* Definir stack en la parte superior de RAM */
    . = ALIGN(8);
    _stack_top = ORIGIN(RAM) + LENGTH(RAM);
}
