Tabla para la cadena de texto `HOLA1234` para diferentes valores de la varibale `KEY`
| Nº | Clave KEY[4] (hexadecimal)                                           | Bloque cifrado (g_encrypted)   | Bloque descifrado (g_decrypted) | Mensaje |
|----|----------------------------------------------------------------------|--------------------------------|---------------------------------|---------|
| 1  | {0x12345678, 0x9ABCDEF0, 0xFEDCBA98, 0x76543210}                     | da21c31f 5e98b1fd              | 414c4f48 34333231               | HOLA1234 |
| 2  | {0x11111111, 0x22222222, 0x33333333, 0x44444444}                     | abb05714 61a3d03e              | 414c4f48 34333231               | HOLA1234 |
| 3  | {0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0xDDDDDDDD}                     | 0cd183b4 33097069              | 414c4f48 34333231               | HOLA1234 |
| 4  | {0x00000000, 0x00000000, 0x00000000, 0x00000000}                     | c1820dd0 2123308b              | 414c4f48 34333231               | HOLA1234 |
| 5  | {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}                     | c1820dd0 2123308b              | 414c4f48 34333231               | HOLA1234 |
| 6  | {0x0F0F0F0F, 0xF0F0F0F0, 0x00FF00FF, 0xFF00FF00}                     | f7608b36 66342441              | 414c4f48 34333231               | HOLA1234 |
| 7  | {0xDEADBEEF, 0xCAFEBABE, 0xFEEDFACE, 0x0BADC0DE}                     | 5c8ce9b5 0b7bf277              | 414c4f48 34333231               | HOLA1234 |
| 8  | {0x01234567, 0x89ABCDEF, 0x76543210, 0xFEDCBA98}                     | 12c2e19b d3fa2f77              | 414c4f48 34333231               | HOLA1234 |

