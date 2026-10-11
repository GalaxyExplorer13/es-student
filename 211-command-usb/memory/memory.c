#include "memory.h"

static void row(const char *name, uintptr_t start, uintptr_t end)
{
    printf("%-10s 0x%08x 0x%08x %8u\n",
           name, (unsigned)start, (unsigned)end, (unsigned)(end - start));
}

void mem_info(void)
{
    printf("%-10s %-10s %-10s %-10s\n", "area", "start","end","size");
    row("flash", XIP_BASE, XIP_BASE + PICO_FLASH_SIZE_BYTES);
    row("sram", SRAM_BASE, SRAM_END);
    row("rom", ROM_BASE, (uintptr_t) (16 * 1024));
    row("image", (uintptr_t)&__flash_binary_start, (uintptr_t)&__flash_binary_end);
    row("free", (uintptr_t)&__flash_binary_end, XIP_BASE + PICO_FLASH_SIZE_BYTES);
    row("boot2", (uintptr_t)&__boot2_start__, (uintptr_t)&__boot2_end__);
    row("text", (uintptr_t)&__boot2_end__, (uintptr_t)&__etext);
    row("data flash", (uintptr_t)&__etext, (uintptr_t)&__etext + (unsigned) (uintptr_t)&__data_end__ - (uintptr_t)&__data_start__);
    row("data ram", (uintptr_t)&__data_start__, (uintptr_t)&__data_end__);
    row("bss", (uintptr_t)&__bss_start__, (uintptr_t)&__bss_end__);
    row("heap", (uintptr_t)&__bss_end__, (uintptr_t)&__HeapLimit);
    row("stack", (uintptr_t)&__StackBottom, (uintptr_t)&__StackTop);

    printf("total\n");
    uint32_t boot2 = (unsigned) ((uintptr_t)&__boot2_end__ - (uintptr_t)&__boot2_start__);
    uint32_t text = (unsigned) ((uintptr_t)&__etext - (uintptr_t)&__boot2_end__);
    uint32_t data = (unsigned) ((uintptr_t)&__data_end__ - (uintptr_t)&__data_start__);

    uint32_t flash_size = (unsigned) (XIP_BASE + PICO_FLASH_SIZE_BYTES - (uintptr_t)XIP_BASE);
    uint32_t flash_free = (unsigned) (XIP_BASE + PICO_FLASH_SIZE_BYTES - (uintptr_t)&__flash_binary_end);
    
    uint32_t bss = (unsigned) ((uintptr_t)&__bss_end__ - (uintptr_t)&__bss_start__);
    uint32_t stack = (unsigned) ((uintptr_t)&__StackTop - (uintptr_t)&__StackBottom);
    uint32_t heap = (unsigned) ((uintptr_t)&__HeapLimit - (uintptr_t)&__bss_end__);

    uint32_t flash_image = boot2 + text + data;
    uint32_t ram_used = data + bss;
    uint32_t flash = ((unsigned) (XIP_BASE + PICO_FLASH_SIZE_BYTES - XIP_BASE));
    uint32_t free = ((unsigned) (XIP_BASE + PICO_FLASH_SIZE_BYTES - (uintptr_t)&__flash_binary_end));

    

    printf("%-2s %8u = %s %8u + %s %8u + %s %8u\n", "flash image", flash_image, 
        "boot2", boot2, "text", text, "data", data );
    printf("%-2s %8u %s %8u\n", "flash free", free, "of", flash);
    printf("%-2s %8u = %s %8u + %s %8u\n", "ram used", ram_used, "data", data, "bss", bss);
    printf("%-2s %8u %s %8u %s\n", "ram free", heap, "for heap and", stack, "for stack");
    
    
}