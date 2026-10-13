#include "memory.h"
#include "command.h"
#include "device.h"
#include <stdlib.h>

uint32_t data_variable = 100;
uint32_t bss_variable;

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

    

    printf("%-2s %8u = %-2s %8u + %-2s %8u + %-2s %8u\n",
         "flash image", flash_image, "boot2", boot2, "text", text, "data", data );
    printf("%-2s %8u %s %8u\n",
         "flash free", free, "of", flash);
    printf("%-2s %8u = %s %8u + %s %8u\n",
         "ram used", ram_used, "data", data, "bss", bss);
    printf("%-2s %8u %s %8u %s\n",
         "ram free", heap, "for heap and", stack, "for stack");
    
    
}

void fw_info(void)
{

     data_variable++;
     bss_variable++;
     int main(void);

     uint16_t *main_code = (uint16_t *)((uintptr_t)main & ~1u);
     uint16_t *fw_info_code = (uint16_t *)((uintptr_t)fw_info & ~1u);
     uint16_t *commands_code = (uint16_t *)((uintptr_t)commands & ~1u);
     uint32_t stack_variable = 1946;
     uint32_t *heap_variable = malloc(sizeof(uint32_t));

     if (heap_variable != NULL)
     {
          *heap_variable = 1951;
     }

     printf("%-18s %-12s %-10s\n", "object", "address", "value");
     printf("%-18s 0x%08x 0x%04x\n", "main",    main_code, *main_code);
     printf("%-18s 0x%08x 0x%04x\n", "fw_info", fw_info,   *fw_info);
     printf("%-18s 0x%08x\n", "commands", commands);
     for (uint i = 0; i <command_count; i++)
     {
          uint16_t *comm = (uint16_t *)((uintptr_t)commands[i].handler & ~1u);
          printf("%-18s 0x%08x\n", commands[i].name, comm);
     }

     printf("%-18s %p  %s\n", "DEVICE_PROJECT",(void*)DEVICE_PROJECT, DEVICE_PROJECT);
     printf("%-18s %p  %s\n", "DEVICE_BOARD",(void*)DEVICE_BOARD,   DEVICE_BOARD);

     printf("%-18s %p  %d\n", "data_variable",  &data_variable,  data_variable);
     printf("%-18s %p  %d\n", "bss_variable",   &bss_variable,   bss_variable);
     printf("%-18s %p  %d\n", "stack_variable", &stack_variable, stack_variable);
     printf("%-18s %p  %d\n", "heap_variable",  heap_variable,   *heap_variable);

     free(heap_variable);

}