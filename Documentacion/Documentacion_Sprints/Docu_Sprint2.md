# Documentación Sprint 2 – Implementación en ASM y Optimización del Proyecto TEA

Este documento resume los pasos realizados en el **Sprint 2**, incluyendo la implementación de las funciones del algoritmo TEA en ensamblador RISC-V, la integración con el proyecto existente, las pruebas de cifrado/descifrado en QEMU con GDB, y la optimización de código para mejorar el rendimiento.

---

## 1. Estructura del proyecto

```
CE4301_P1/
├── Codigo_Fuente/
│   └── proyecto-tea/
│       ├── src/ # Código fuente
│       │   ├── main.c
│       │   ├── tea.c
│       │   ├── tea.h
│       │   ├── tea_encrypt.s # Implementación ASM (cifrado TEA)
│       │   ├── tea_decrypt.s # Implementación ASM (descifrado TEA)
│       │   └──startup.s # Código de arranque
│       ├── linker.ld # Script de enlace
│       ├── build.sh # Script de compilación
│       ├── run-qemu.sh # Script para ejecutar QEMU
│       ├── run.sh # Script para iniciar Docker/QEMU  
│       └── test.elf # Binario generado
└── Documentacion/
    ├── Documentacion_Sprints
    │   ├── Docu_Sprint1.md 
    │   └── Docu_Sprint2.md
    └── README.md # Documentación final del proyecto
```

---

## 2. Implementación en ASM

### Funciones migradas a ensamblador RISC-V

Se implementaron las versiones en ASM del algoritmo TEA:

- `tea_encrypt_asm`: realiza las 32 rondas de cifrado.
- `tea_decrypt_asm`: realiza las 32 rondas de descifrado.

Ambas funciones están definidas en los archivos `tea_encrypt.s` y `tea_decrypt.s` respectivamente, utilizando la convención de nombres:

```asm
.globl tea_encrypt_asm
.globl tea_decrypt_asm
```

Esto evita colisiones con las funciones de C y resuelve errores de `multiple definition` y `undefined reference` durante el enlace.

### Integración con main.c

El flujo de prueba en `main.c` fue modificado para llamar directamente a las funciones en ensamblador cuando se compila con la macro `-DTEA_USE_ASM`. Esto se logra mediante directivas de compilación condicionales en el código fuente, permitiendo seleccionar entre la implementación en C o en ASM según la configuración de compilación.

Por ejemplo:

```c
#ifdef TEA_USE_ASM
extern void tea_encrypt_asm(uint32_t* v, const uint32_t* k);
extern void tea_decrypt_asm(uint32_t* v, const uint32_t* k);
#define tea_encrypt tea_encrypt_asm
#define tea_decrypt tea_decrypt_asm
#else
void tea_encrypt(uint32_t* v, const uint32_t* k);
void tea_decrypt(uint32_t* v, const uint32_t* k);
#endif
```

De esta forma, el resto del código puede seguir llamando a `tea_encrypt` y `tea_decrypt` de manera transparente.

---

## 3. Scripts actualizados

### build.sh

- Se actualizó para compilar los archivos `tea_encrypt.s` y `tea_decrypt.s` junto con el resto del proyecto.
- Se añadió la macro `-DTEA_USE_ASM` para habilitar las llamadas a las funciones en ASM.
- Se agregó limpieza de objetos antiguos antes de compilar para evitar conflictos de enlace.

Ejemplo de comandos relevantes en `build.sh`:

```bash
rm -f *.o test.elf
riscv64-unknown-elf-gcc -c tea_encrypt.s -o tea_encrypt.o
riscv64-unknown-elf-gcc -c tea_decrypt.s -o tea_decrypt.o
riscv64-unknown-elf-gcc -DTEA_USE_ASM -c main.c -o main.o
# ...compilación de otros archivos...
riscv64-unknown-elf-gcc -nostartfiles -T linker.ld *.o -o test.elf
```

### run-qemu.sh y run.sh

- Mantuvieron su función original: iniciar QEMU en modo bare-metal y permitir depuración con GDB.
- No requirieron cambios estructurales para este sprint.

### linker.ld y startup.s

- Mantuvieron la configuración establecida en el Sprint 1.
- El punto de entrada sigue siendo `_start`, que realiza la inicialización de stack y el salto a `main`.

---

## 4. Pruebas en QEMU + GDB

### Compilación

En el contenedor (terminal 1):

```bash
cd /home/rvqemu-dev/workspace/proyecto-tea
chmod +x build.sh
./build.sh
```

Esto genera el archivo `test.elf` a partir de `main.c`, `tea.c`, `startup.s` y `linker.ld`, incluyendo ahora las implementaciones en ASM del cifrado y descifrado.

### Ejecución y depuración

**Paso 1: Iniciar QEMU con servidor GDB**  
En la primera terminal (dentro del contenedor):

```bash
chmod +x run-qemu.sh
./run-qemu.sh
```

Esto arranca QEMU y queda a la espera de conexión por GDB en el puerto `1234`.

**Paso 2: Conectar GDB**  
En la segunda terminal:

```bash
docker exec -it rvqemu /bin/bash
cd /home/rvqemu-dev/workspace/proyecto-tea
gdb-multiarch test.elf
```

Dentro de GDB:

```bash
target remote :1234
break main
continue
```

Con esto basta para poder empezar a depurar el código C.

### Comandos útiles de depuración

- Ver bloques de memoria:

  ```bash
  x/4wx &g_plain        # Texto plano
  x/4wx &g_encrypted    # Texto cifrado
  x/4wx &g_decrypted    # Texto descifrado
  p/x g_ok              # Verificar bandera
  ```

- Control de ejecución:

  ```bash
  next          # Ejecutar siguiente instrucción en C
  step          # Entrar a funciones
  continue      # Continuar ejecución
  Ctrl+C        # Interrumpir ejecución (por loop infinito)
  ```

### Resultados de pruebas

Se verificó el correcto funcionamiento de las funciones en ASM mediante pruebas de cifrado y descifrado, confirmando que `decrypt(encrypt(x)) == x` para diversos valores de `x`.

---

## 5. Resumen del Sprint 2

Durante este sprint se realizaron los siguientes pasos:

1. **Implementación de funciones en ASM** para el algoritmo TEA, con integración en el proyecto existente.
2. **Actualización de scripts de compilación** (`build.sh`) para incluir las nuevas funciones y permitir su selección mediante macros.
3. **Pruebas exhaustivas en QEMU** para validar el correcto cifrado y descifrado de datos.
4. **Depuración en GDB** para asegurar el correcto flujo de ejecución y la integridad de los datos.

---

## 6. Estado final

El proyecto está correctamente configurado y ejecutándose en un entorno RISC-V bare-metal simulado con QEMU, validando con pruebas de cifrado y descifrado en GDB. Las funciones en ASM del algoritmo TEA están integradas y operativas, con un rendimiento mejorado en comparación con la implementación original en C.
