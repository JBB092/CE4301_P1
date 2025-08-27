# Documentación Sprint 1 – Configuración Inicial del Proyecto TEA

Este documento resume los pasos realizados en el **Sprint 1**, incluyendo la configuración del entorno de desarrollo, la compilación y ejecución del proyecto TEA en arquitectura RISC-V dentro de QEMU, y la verificación mediante GDB.

---

## 1. Estructura del proyecto

```

CE4301_P1/
├── Codigo_Fuente/
│ └── proyecto-tea/
│ ├── src/ # Código fuente
│ │ ├── main.c
│ │ ├── tea.c
│ │ └── tea.h
│ ├── startup.s # Código de arranque
│ ├── linker.ld # Script de enlace
│ ├── build.sh # Script de compilación
│ ├── run-qemu.sh # Script para ejecutar QEMU
│ └── test.elf # Binario generado
└── Documentacion/
└── Docu_Sprint1.md # Documentación del sprint


```

---

## 2. Configuración del entorno

1. **Construcción del contenedor Docker**  
   Desde la raíz del proyecto:
   ```bash
   chmod +x run.sh
   ./run.sh
 Esto construye la imagen `rvqemu` y lanza un contenedor con el toolchain RISC-V y QEMU ya configurados.

2. **Ejecución del contenedor**
   Una vez creado, el contenedor monta el directorio del proyecto en:
   ```bash
   /home/rvqemu-dev/workspace

3. **Compilación del proyecto TEA**
   Dentro del contenedor (primera terminal):
   ```bash
   cd /home/rvqemu-dev/workspace/proyecto-tea
   chmod +x build.sh
   ./build.sh
Esto genera el archivo `test.elf` a partir de `main.c`, `tea.c`, `startup.s` y `linker.ld`.

4. **Ejecución y depuración con QEMU + GDB**
**Paso 1: Iniciar QEMU con servidor GDB**
En la primera terminal (dentro del contenedor):
   ```bash
   chmod +x run-qemu.sh
   ./run-qemu.sh
Esto arranca QEMU y queda a la espera de conexión por GDB en el puerto `1234`
**Paso 2: Conectar GDB**
En la segunda terminal:
   ```bash
   docker exec -it rvqemu /bin/bash
   cd /home/rvqemu-dev/workspace/proyecto-tea
   gdb-multiarch test.elf
Dentro de GBD:
   ```bash
   target remote :1234
   break main
   continue
Con esto basta para poder empezar a depurar el código C

5. **Comandos útiles de depuración**
- Ver bloques de memoria:
   ```bash
   x/4wx &g_plain        # Texto plano
   x/4wx &g_encrypted    # Texto cifrado
   x/4wx &g_decrypted    # Texto descifrado
   p/x g_ok              # Verificar bandera
- Control de ejecución:
   ```bash
   next          # Ejecutar siguiente instrucción en C
   step          # Entrar a funciones
   continue      # Continuar ejecución
   Ctrl+C        # Interrumpir ejecución (por loop infinito)

6. **Resumen del Sprint 1**
Durante este sprint se realizaron los siguientes pasos:
1. **Configuración del entorno Docker** con toolchain RISC-V y QEMU.
2. **Creación de scripts** (`build.sh`, `run-qemu.sh`, `run.sh`) para automatizar la compilación y ejecución.
3. **Implementación del código fuente inicial:**
* `main.c`: flujo de prueba de algoritmo TEA (encrypt/decrypt).
* `tea.c` y `tea.h`: implementación del algoritmo TEA.
* `startup.s`: inicialización básica y salto a `main`.
* `linker.ld`: script de enlazado para arquitectura RISC-V bare-metal.
4. **Ejecución en QEMU** de un programa bare-metal.
5. **DEpuración en GDB:**
* Inspección de bloques de texto plano, cifrado y descifrado.
* Validación de la bandera `g.ok` con valor `0x600D600D` indicando éxito.
6. **Validación final:** se confirmó que `decrypt(encrypt(x)) == x`.

7. Estado final
El proyecto está correctamente configurado y ejecutándose en un entorno RISC-V bare-metal simulado con QEMU, validando con pruebas de cifrado y descifrado en GDB.
