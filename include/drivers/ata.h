#pragma once

#include <stdint.h>

#define ATA_BASE           0x1F0
#define ATA_SLAVE_BASE     0x170
#define ATA_MASTER           0x0

#define DATA        ATA_BASE + 0
#define ERREG       ATA_BASE + 1
#define FEATURES    ATA_BASE + 1
#define SECT_CNT    ATA_BASE + 2
#define SECT_NUM    ATA_BASE + 3
#define CYL_LOW     ATA_BASE + 4
#define CYL_HIGH    ATA_BASE + 5
#define DRIVE_SEL   ATA_BASE + 6
#define STATUS      ATA_BASE + 7
#define COMMAND     ATA_BASE + 7


#define MASTER_DRIVE        0xA0
#define SLAVE_DRIVE         0xB0
#define IDENTIFY            0xEC
#define READ_SECTORS        0x20

typedef enum {
    ERR,
    IDX,
    CORR,
    DRQ,
    SRV,
    DF,
    RDY,
    BSY

} drive_status_t;

void ata_init();
drive_status_t drive_status(uint8_t drive);
void select_drive(uint8_t bus, uint8_t dn);
void delay_400ns();
void read_sectors(uint32_t sector_count, uint32_t lba, void* dest);
