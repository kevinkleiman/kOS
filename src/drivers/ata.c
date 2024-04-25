#include "drivers/ata.h"
#include "stdio.h"
#include "io.h"


void ata_init()
{
    uint16_t* buf;
    select_drive(ATA_MASTER, ATA_MASTER);
    read_sectors(2, 0x0, (void*) buf);

    printk("Sectors=%x\n", buf);
}

/* Get drive status */
drive_status_t drive_status(uint8_t drive)
{
    uint8_t status = inb(STATUS);

    // check if drive is busy first
    if(status & (1 << BSY)) return BSY;
    if(status & (1 << ERR)) return ERR;
    if(status & (1 << RDY)) return RDY;

    return status & (1 >> DF);
}

/* Select a drive to read/write */
void select_drive(uint8_t bus, uint8_t dn)
{
    if(bus == ATA_MASTER) {
        if(dn == ATA_MASTER) outb(DRIVE_SEL, MASTER_DRIVE);
        else outb(DRIVE_SEL, SLAVE_DRIVE);
    } else {
        if(dn == ATA_MASTER) outb(ATA_SLAVE_BASE + 6, SLAVE_DRIVE);
        else outb(ATA_SLAVE_BASE + 6, SLAVE_DRIVE);
    }
}

/* Wait 400 nano seconds for read delay */
void delay_400ns()
{
    for (int i = 0; i < 4; i++);
}

/* Read n sectors from disk */
void read_sectors(uint32_t sector_count, uint32_t lba, void* dest)
{
    outb(DRIVE_SEL, 0xE0 | (uint8_t) ((lba >> 24) & 0xF));
    outb(FEATURES, 0x0);
    outb(SECT_CNT, sector_count);
    outb(SECT_NUM, (uint8_t) lba);
    outb(CYL_LOW, (uint8_t) lba >> 8);
    outb(CYL_HIGH, (uint8_t) lba >> 16);
    outb(COMMAND, READ_SECTORS);

    uint16_t* tmp = (uint16_t*) dest;

    for(int i = 0; i < (sector_count * 256); i += 256)
    {
        // poll drive status
        while(drive_status(0) == BSY);

        for(int j = 0; j < 256; ++j) {
            tmp[j + i] = inw(ATA_BASE);
        }

        delay_400ns();
    }

    dest = (void*) tmp;
}
