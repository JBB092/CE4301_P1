# Estructura del Proyecto
A continuación se comparte la estructura del proyecto:

```
CE4301_P1/
├── Codigo_Fuente/
│   └── proyecto-tea/
│       ├── src/                  # Código fuente
│       │   ├── main.c
│       │   ├── tea.c
│       │   ├── tea.h
│       │   ├── tea_encrypt.s     # Implementación ASM (cifrado TEA)
│       │   ├── tea_decrypt.s     # Implementación ASM (descifrado TEA)
│       │   ├── padding.c         # Implementación PKCS#7
│       │   ├── padding.h         # Cabecera de PKCS#7
│       │   └── startup.s         # Código de arranque
│       ├── linker.ld             # Script de enlace
│       ├── build.sh              # Script de compilación
│       ├── run-qemu.sh           # Script para ejecutar QEMU
│       ├── run.sh                # Script para iniciar Docker/QEMU
│       └── test.elf              # Binario generado
└── Documentacion/
    ├── Documentacion_Sprints/
    │   ├── Docu_Sprint1.md
    │   ├── Docu_Sprint2.md
    │   └── Docu_Sprint3.md       # Este documento
    └── README.md                 # Documentación final del proyecto
```

# Guía de Uso Rápida para QEMU+GDB (para más información ver la documentación del proyecto `proyecto-tea`)

1. **Construcción del contenedor Docker**  
   Desde la raíz del proyecto:
   ```bash
   chmod +x run.sh
   ./run.sh
   ```
   Esto construye la imagen `rvqemu` y lanza un contenedor con el toolchain RISC-V y QEMU ya configurados.

2. **Ejecución del contenedor**  
   Una vez creado, el contenedor monta el directorio del proyecto en:
   ```bash
   /home/rvqemu-dev/workspace
   ```

3. **Compilación del proyecto TEA**  
   Dentro del contenedor (primera terminal):
   ```bash
   cd /home/rvqemu-dev/workspace/proyecto-tea
   chmod +x build.sh
   ./build.sh
   ```
   Esto genera el archivo `test.elf` a partir de `main.c`,`padding.c` `tea_encrypt.s`, `tea_decrypt.s`, `startup.s` y `linker.ld`.

4. **Ejecución y depuración con QEMU + GDB**

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

5. **Comandos útiles de depuración**
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

# Guía de Uso Rápida para QEMU con `print` implementado (para más información ver la documentación del proyecto `baremetal-printf`)

1. **Construcción del contenedor Docker**  
   Desde la raíz del proyecto:
   ```bash
   chmod +x run.sh
   ./run.sh
   ```
   Esto construye la imagen `rvqemu` y lanza un contenedor con el toolchain RISC-V y QEMU ya configurados.

2. **Ejecución del contenedor**  
   Una vez creado, el contenedor monta el directorio del proyecto en:
   ```bash
   /home/rvqemu-dev/workspace
   ```

3. **Compilación del proyecto TEA**  
   Dentro del contenedor (primera terminal):
   ```bash
   cd /home/rvqemu-dev/workspace/proyecto-tea
   chmod +x build.sh
   ./build.sh
   ```
   Esto genera el archivo `test.elf` a partir de `main.c`,`padding.c` `tea_encrypt.s`, `tea_decrypt.s`, `uart.c`, `print.c`, `print_hex.c`, `startup.s` y `linker.ld`.

4. **Ejecución de QEMU con `print`**

   **Paso 1: Iniciar QEMU**  
   En la primera terminal (dentro del contenedor):
   ```bash
   chmod +x run-qemu.sh
   ./run-direct.sh
   ```
   Esto arranca QEMU y ejecuta el archivo `test.elf` donde se podrá ver en consola las impresiones colocadas.
