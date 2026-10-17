#include <stdio.h>
#include <stdint.h> // ради типа uintptr_t
#include "hardware/regs/addressmap.h"
#include "pico/stdlib.h"
#include "hardware/regs/sio.h"
#define VECTOR_TABLE 0x10000100




void mem_info(void);
void fw_info(void);
void boot_info(void);
static void row(const char *name, uintptr_t start, uintptr_t end);