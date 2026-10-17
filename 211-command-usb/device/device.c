#include "device.h"
#include "log.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/unique_id.h"
#include "hardware/regs/addressmap.h"
#include "hardware/regs/sysinfo.h"
#include "pico/version.h"
#include <stddef.h>

struct info_t device_card;  // Определение глобальной переменной


void init_device_card(void)
{
    volatile uint32_t *chip_id_for_card = (uint32_t *)(SYSINFO_BASE + SYSINFO_CHIP_ID_OFFSET);
    uint32_t id = *chip_id_for_card;

    uint32_t revision_for_card =
        (id & SYSINFO_CHIP_ID_REVISION_BITS) >> SYSINFO_CHIP_ID_REVISION_LSB;

    device_card.revision = revision_for_card;
    device_card.version = 0x00000100;
    snprintf(device_card.name, sizeof(device_card.name), "es-cmd-usb");
}

void dev_info(void)
{
printf("%-13s %-13s %-13s %-13s %-13s\n", "struct","address","size","offset","value");

printf("%-13s 0x%08x %5u\n",
     "device_card", &device_card, sizeof(device_card.revision));

printf("- %-13s 0x%08x %5u %6u %6u\n",
     "revision", &device_card.revision, sizeof(device_card.revision), offsetof(struct info_t, revision),
           device_card.revision);

printf("- %-13s 0x%08x %5u %6u 0x%08x\n",
     "version", &device_card.version, sizeof(device_card.version), offsetof(struct info_t, version),
           device_card.version);
           
printf("- %-13s 0x%08x %5u %6u %6s\n",
     "name", device_card.name, sizeof(device_card.name), offsetof(struct info_t, name),
           device_card.name);

unsigned fields = sizeof(device_card.version) + sizeof(device_card.name) + sizeof(device_card.revision);
size_t size = sizeof(device_card);
uint8_t padding = size - fields;
printf("%s %u %s %u %s %u", "fields",fields, "sizeof",size, "padding",padding);

}


void device_info(void)
{
    // board id
    char board_id[PICO_UNIQUE_BOARD_ID_SIZE_BYTES * 2 + 1];
    pico_get_unique_board_id_string(board_id, sizeof(board_id));

    // chip id
    volatile uint32_t *chip_id = (uint32_t *)(SYSINFO_BASE + SYSINFO_CHIP_ID_OFFSET);
    uint32_t id = *chip_id;

    uint32_t manufacturer =
        (id & SYSINFO_CHIP_ID_MANUFACTURER_BITS) >> SYSINFO_CHIP_ID_MANUFACTURER_LSB;
    uint32_t part =
        (id & SYSINFO_CHIP_ID_PART_BITS) >> SYSINFO_CHIP_ID_PART_LSB;
    uint32_t revision =
        (id & SYSINFO_CHIP_ID_REVISION_BITS) >> SYSINFO_CHIP_ID_REVISION_LSB;

    // вывод
    printf("DEVICE_PROJECT: %8u, %s\n", &DEVICE_PROJECT, DEVICE_PROJECT);
    printf("device name:    %s\n", DEVICE_NAME);
    printf("DEVICE_BOARD:   %8u, %s\n", &DEVICE_BOARD, DEVICE_BOARD);
    printf("serial:  %s\n", board_id);
    printf("chip:    manufacturer 0x%03x, part 0x%04x, revision %u\n", manufacturer, part, revision);
    printf("pico-sdk: %s\n", PICO_SDK_VERSION_STRING);
}