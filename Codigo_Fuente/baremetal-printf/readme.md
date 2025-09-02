# Baremetal Printf en QEMU (RISC-V)

Este mini–proyecto implementa un `printf` minimalista en un entorno **bare–metal** utilizando **QEMU-RISC-V**.  
Se evita el uso de librerías estándar como `newlib`, y se implementa desde cero un módulo **UART** y un `printf` básico que soporta:

- Cadenas (`%s`)
- Enteros decimales (`%d`)
- Enteros hexadecimales (`%x`)

El objetivo es entender el flujo completo: **desde el arranque de la CPU → ejecución del `printf` → salida en consola a través de UART en QEMU**.

---

## Estructura del Proyecto

```

baremetal-printf/
├── build.sh           # Script de compilación del proyecto
├── Dockerfile         # Entorno reproducible con toolchain cruzada
├── linker.ld          # Script de linkeo para memoria bare-metal RISC-V
├── main.o             # Objeto compilado de main.c
├── print.o            # Objeto compilado de print.c
├── run-direct.sh      # Ejecuta directamente en QEMU
├── run-qemu.sh        # Ejecuta test.elf en QEMU (esperando GDB)
├── run.sh             # Script principal (build + run en QEMU)
├── startup.o          # Objeto compilado de startup.s
├── test.elf           # Binario final enlazado
├── uart.o             # Objeto compilado de uart.c
├── src/
│   ├── main.c         # Programa principal de prueba
│   ├── print.c        # Implementación de printf minimalista
│   ├── print.h        # Header de printf
│   ├── startup.s      # Código de arranque en ensamblador RISC-V
│   ├── uart.c         # Implementación de UART
│   └── uart.h         # Header de UART
└── Documentacion/
└── readme.md      # Documentación detallada del proyecto

```

---

### Requisitos previos

Antes de ejecutar el mini-proyecto, es necesario contar con lo siguiente instalado en la computadora:  

- **Docker** (indispensable, ya que el proyecto corre en un contenedor).  
- **Git** (para clonar el repositorio si aún no se tiene).  
- **Un editor de texto** (ej. VSCode, Vim, Nano) para editar el mensaje y la llave (KEY) en el archivo `main.c`.  

Dentro del archivo `main.c` se puede configurar lo que se desea imprimir utilizando el comando `print()` 

---

## Guía de Uso
### 1. Inicialización del contenedor Docker
Ejecutar el siguiente comando en la terminal dentro de la carpeta `baremeta-printf` usando los siguientes comandos

```bash
chmod +x ./run.sh
./run.sh
```
Esto iniciará el contenedor Docker configurado para QEMU.

### 2. Compilación de los archivos
Una vez dentro del contenedor, dar permisos al script `build.sh` y ejecutarlo para compilar el proyecto:

```bash
chmod +x ./build.sh
./build.sh
```

### 3. Ejecutar en QEMU

Ejecuta directamente el binario en QEMU y muestra la salida en consola:

```bash
./run-direct.sh
```

### 4. Ejecutar QEMU con GDB (modo depuración)

Para iniciar QEMU en modo espera de GDB:

```bash
./run-qemu.sh
```

Esto deja QEMU corriendo y esperando en el puerto `:1234`.

### 5. Conectarse con GDB

En otra terminal, dentro de la misma carpeta `baremetal-printf`, conectarse al contenedor que ya está corriendo:

```bash
docker exec -it rvqemu /bin/bash
```

Dentro del contenedor, ejecutar:

```bash
gdb-multiarch test.elf
```

Y luego para poder conectarse de forma remota a la otra terminal ejecutar lo siguiente:

Una vez en GDB, conectarse al puerto 1234 que QEMU abrió previamente:

```bash
target remote :1234
```

### 6. Comandos útiles en GDB

* **Ejecutar hasta main**:

  ```gdb
  break main
  continue
  ```
* **Paso a paso**:

  ```gdb
  step     # entra en funciones
  next     # siguiente instrucción sin entrar
  ```
* **Inspeccionar variables**:

  ```gdb
  info locals
  print variable
  ```
* **Ver memoria (ejemplo dirección 0x80000000)**:

  ```gdb
  x/16wx 0x80000000
  ```
* **Salir de GDB**:

  ```gdb
  quit
  ```

---

## Ejemplo de salida en consola

Al ejecutar el programa, debería ver algo similar:

```bash
Hola baremetal!
Numero decimal: 1234
Numero hexadecimal: 0x0000BEEF
Caracter: A
Cadena: Embebidos
```
