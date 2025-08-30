# Documentación Sprint 3 – Implementación de Padding PKCS#7 y Pruebas con Mensajes Múltiples

Este documento resume los pasos realizados en el **Sprint 3**, incluyendo la implementación del esquema de padding **PKCS#7**, la integración con el proyecto TEA en C/ASM, y la validación mediante pruebas con diferentes mensajes y claves. Se realizaron modificaciones al flujo de cifrado/descifrado para soportar múltiples bloques y se documentaron los resultados experimentales.

---

## 1. Estructura del proyecto

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

---

## 2. Implementación del Padding PKCS#7

### 2.1 ¿Qué es PKCS#7?

El padding **PKCS#7** es un esquema estándar usado en criptografía para rellenar mensajes de manera que su longitud sea múltiplo del tamaño de bloque (en este caso, **8 bytes para TEA**) [1].

- Si al mensaje le faltan *N* bytes para completar el bloque, se agregan *N* bytes con el valor `N` [1].
- Si el mensaje ya es múltiplo del tamaño del bloque, se añade un bloque completo de padding con valor igual al tamaño del bloque [1].

**Ejemplo:**
- Mensaje `"HOLA"` (4B) → relleno con `04 04 04 04`.
- Mensaje `"TEC"` (3B) → relleno con `05 05 05 05 05`.

Este método está definido formalmente en el estándar **RFC 5652 (Cryptographic Message Syntax - CMS)**, el cual describe cómo realizar el relleno PKCS#7 para algoritmos de bloque [1].

---

### 2.2 Archivos añadidos

- **`padding.c`**: implementación de `pkcs7_pad` y `pkcs7_unpad`.
- **`padding.h`**: cabecera con prototipos de funciones.

---

### 2.3 Integración en `main.c`

Se modificó el flujo de `main.c` para:

1. Aplicar **PKCS#7** al mensaje original.
2. Cifrar bloque por bloque (8B cada bloque).
3. Descifrar bloque por bloque.
4. Remover padding para recuperar el mensaje original.

Esto permite probar mensajes de **longitudes variables** y verificar que `decrypt(encrypt(x)) == x`.

---

## 3. Scripts y compilación

### 3.1 `build.sh`

Se actualizó para incluir `padding.c` en el proceso de compilación:

```bash
riscv64-unknown-elf-gcc -c padding.c -o padding.o
riscv64-unknown-elf-gcc -DTEA_USE_ASM -c main.c -o main.o
riscv64-unknown-elf-gcc -nostartfiles -T linker.ld *.o -o test.elf
```

---

### 3.2 `run.sh` y `run-qemu.sh`

No requirieron cambios, mantienen la lógica de ejecutar QEMU en modo bare-metal y exponer el puerto para conexión con GDB.

---

## 4. Pruebas en QEMU + GDB

### 4.1 Procedimiento

1. Compilar el proyecto con:

   ```bash
   ./build.sh
   ```

2. Ejecutar QEMU:

   ```bash
   ./run-qemu.sh
   ```

3. Conectar GDB:

   ```bash
   gdb-multiarch test.elf
   target remote :1234
   ```

4. Observar los resultados en memoria:

   ```bash
   x/20bx g_plain
   x/20bx g_encrypted
   x/20bx g_decrypted
   x/20bx g_unpadded
   p/x g_ok
   ```

---

## 5. Resultados importantes

### 5.1 Pruebas con múltiples mensajes (PKCS#7 + TEA)

| #  | Mensaje (input)                | `g_plain` (hex)                                                           | `g_encrypted` (hex)                                           | `g_decrypted` (hex)                                                       | `g_unpadded` (hex)                                                | Bandera      |
|----|------------------------------- |---------------------------------------------------------------------------|---------------------------------------------------------------|---------------------------------------------------------------------------|-------------------------------------------------------------------|--------------|
| 1  | `"HOLA"` (4B)                  | `48 4F 4C 41 04 04 04 04`                                                 | `0F 93 D3 2F 19 AE 43 1F`                                     | `48 4F 4C 41 04 04 04 04`                                                 | `48 4F 4C 41`                                                     | `0x600D600D` |
| 2  | `"TEC"` (3B)                   | `54 45 43 05 05 05 05 05`                                                 | `93 89 D5 3B 18 FA 9A D6`                                     | `54 45 43 05 05 05 05 05`                                                 | `54 45 43`                                                        | `0x600D600D` |
| 3  | `"EMBEBIDOS"` (9B)             | `45 4D 42 45 42 49 44 4F 53 07 07 07 07 07 07 07`                         | `7E 4D 86 4F 73 7F 24 B3 1C C1 A8 2C AB 35 E2 94`             | `45 4D 42 45 42 49 44 4F 53 07 07 07 07 07 07 07`                         | `45 4D 42 45 42 49 44 4F 53`                                      | `0x600D600D` |
| 4  | `"MICROCONTROLADOR"` (16B)     | `4D 49 43 52 4F 43 4F 4E 54 52 4F 4C 41 44 4F 52 08 08 08 08 08 08 08 08` | `26 BB 42 80 90 13 22 0B 3D 80 C2 6D CF 5D EF 88 BD FE 1F CE` | `4D 49 43 52 4F 43 4F 4E 54 52 4F 4C 41 44 4F 52 08 08 08 08 08 08 08 08` | `4D 49 43 52 4F 43 4F 4E 54 52 4F 4C 41 44 4F 52`                 | `0x600D600D` |
| 5  | `"Mensaje de prueba para TEA"` | `4D 65 6E 73 61 6A 65 20 64 65 20 70 72 75 65 62 61 20 70 61 ...`         | `CC 74 BD C4 6E 97 0E D8 FA 26 50 79 BA CF 26 3A 4F 58 F1 4E` | `4D 65 6E 73 61 6A 65 20 64 65 20 70 72 75 65 62 61 20 70 61 ...`         | `4D 65 6E 73 61 6A 65 20 64 65 20 70 72 75 65 62 61 20 70 61 ...` | `0x600D600D` |

---

### 5.2 Pruebas con distintos valores de la clave `KEY`

| Nº | Clave KEY\[4] (hexadecimal)                      | Bloque cifrado (g_encrypted) | Bloque descifrado (g_decrypted) | Mensaje   |
|----|--------------------------------------------------|------------------------------|----------------------------------|-----------|
| 1  | {0x12345678, 0x9ABCDEF0, 0xFEDCBA98, 0x76543210} | da21c31f 5e98b1fd            | 414c4f48 34333231                | HOLA1234  |
| 2  | {0x11111111, 0x22222222, 0x33333333, 0x44444444} | abb05714 61a3d03e            | 414c4f48 34333231                | HOLA1234  |
| 3  | {0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD} | 0cd183b4 33097069            | 414c4f48 34333231                | HOLA1234  |
| 4  | {0x00000000, 0x00000000, 0x00000000, 0x00000000} | c1820dd0 2123308b            | 414c4f48 34333231                | HOLA1234  |
| 5  | {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF} | c1820dd0 2123308b            | 414c4f48 34333231                | HOLA1234  |
| 6  | {0x0F0F0F0F, 0xF0F0F0F0, 0x00FF00FF, 0xFF00FF00} | f7608b36 66342441            | 414c4f48 34333231                | HOLA1234  |
| 7  | {0xDEADBEEF, 0xCAFEBABE, 0xFEEDFACE, 0x0BADC0DE} | 5c8ce9b5 0b7bf277            | 414c4f48 34333231                | HOLA1234  |
| 8  | {0x01234567, 0x89ABCDEF, 0x76543210, 0xFEDCBA98} | 12c2e19b d3fa2f77            | 414c4f48 34333231                | HOLA1234  |

---

## 6. Diseño y decisiones

### 6.1 Elección de PKCS#7

Se eligió **PKCS#7** frente a otros métodos de padding (como rellenar con ceros) por las siguientes razones:

1. **Desambiguación**: con padding de ceros no es posible diferenciar entre un mensaje que realmente termina en `00` y un `00` añadido como relleno. PKCS#7 resuelve esto gracias al uso de valores explícitos (ej. `04 04 04 04`).
2. **Estándar en criptografía**: PKCS#7 es ampliamente utilizado en AES, DES, TEA y otros algoritmos de bloque, lo que facilita compatibilidad futura.
3. **Simplicidad de implementación**: su lógica es directa y consistente tanto para añadir como para quitar padding.
4. **Robustez en pruebas**: asegura que siempre se añada un bloque de padding incluso si el mensaje ya es múltiplo del tamaño de bloque, evitando ambigüedad.

---

## 7. Resumen del Sprint 3

Durante este sprint se realizaron los siguientes pasos:

1. **Implementación del padding PKCS#7** para TEA.
2. **Integración en `main.c`** para manejar mensajes de longitud variable.
3. **Validación en QEMU + GDB** de múltiples mensajes con y sin padding.
4. **Pruebas con distintas claves** para verificar robustez del sistema.
5. **Documentación de resultados experimentales** mediante tablas comparativas.

---

## 8. Estado final

El proyecto ahora soporta mensajes de **longitudes arbitrarias** mediante el uso de **PKCS#7**. Todas las pruebas confirmaron que `decrypt(encrypt(x)) == x` tras remover el padding, validando la correcta integración del esquema de relleno y su interoperabilidad con la implementación TEA en ASM.

## Referencias
[1] Housley, R. (2009). *RFC 5652: Cryptographic Message Syntax (CMS)*. Internet Engineering Task Force (IETF). Disponible en: https://www.rfc-editor.org/rfc/rfc5652 
