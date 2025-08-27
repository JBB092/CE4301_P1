ENTRY(_start)

SECTIONS
{
  /* Dirección de inicio del programa en QEMU (virt machine) */
  . = 0x80000000;

  .text : {
    *(.text*)         /* Código de funciones */
    *(.text.startup)  /* Opcional, para inicializaciones */
  }

  .rodata : { *(.rodata*) }   /* Datos de solo lectura */
  .data   : { *(.data*) }     /* Variables inicializadas */
  .bss    : { 
    *(.bss*)          /* Variables sin inicializar */
    *(COMMON)
  }

  /* Definir un stack sencillo de 64KB */
  . = ALIGN(8);
  _stack_top = . + 0x10000;   /* 64KB de stack */
}
