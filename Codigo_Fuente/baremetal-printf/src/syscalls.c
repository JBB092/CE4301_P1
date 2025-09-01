#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "uart.h"

#ifndef S_IFCHR
#define S_IFCHR 0x2000
#endif

int _write(int file, const void *ptr, size_t len) {
    const char *cptr = (const char *)ptr;
    for (size_t i = 0; i < len; i++) {
        if (cptr[i] == '\n')
            uart_putc('\r');
        uart_putc(cptr[i]);
    }
    return len;
}

int _read(int file, void *ptr, size_t len) {
    errno = ENOSYS;
    return -1;
}

int _close(int file) {
    return -1;
}

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file) {
    return 1;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}
