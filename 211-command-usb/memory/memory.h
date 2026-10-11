#include <stdio.h>
#include <stdint.h> // ради типа uintptr_t
#include "hardware/regs/addressmap.h"
#include "pico/stdlib.h"


extern char __flash_binary_start;
extern char __flash_binary_end;
extern char __boot2_start__;
extern char __boot2_end__;
extern char __etext;
extern char __data_start__;
extern char __data_end__;
extern char __bss_start__;
extern char __bss_end__;
extern char __HeapLimit;
extern char __StackBottom;
extern char __StackTop;


void mem_info(void);
static void row(const char *name, uintptr_t start, uintptr_t end);