#pragma once

#include <stdint.h>

#define ATA_BASE           0x1F0
#define ATA_SLAVE_BASE     0x170
#define ATA_MASTER          0x00
#define ATA_SLAVE           0x01

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


#define MASTER_DRIVE        0xE0
#define SLAVE_DRIVE         0xF0
#define IDENTIFY            0xEC
#define READ_SECTORS        0x20
#define WRITE_SECTORS        0x30

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
void delay_400ns();
void select_drive(uint8_t bus, uint8_t dn);
void rw_sectors(uint8_t mode, uint8_t drive, uint32_t sector_count, uint32_t lba, void* dest);

drive_status_t drive_status(uint8_t drive);
