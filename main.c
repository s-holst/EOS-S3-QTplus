/* Copyright 2021 Stefan Holst

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

#include <stdint.h>
#include <stdio.h>
#include <sys/param.h>

#include "regs/aip.h"
#include "regs/cru.h"

#include "uart.h"
#include "i2c.h"
#include "spi.h"
#include "io.h"

extern uint32_t uptime_ms; // global from startup.c

extern uint32_t __etext;
extern uint32_t __data_start__;
extern uint32_t __data_end__;

typedef struct
{
    uint16_t dwords;    // download size in double(8-byte)-words minus 1.
    uint8_t baudr_mult; // baudrate multiplier SPI->BAUDR is set to 2*baudr_mult.
    uint8_t id;         // id for EOS S3, must be 0x20.
} tFlashBootHeader;

int main(void)
{
    uint32_t rom_bytes = (uint32_t)&__etext + ((uint32_t)&__data_end__ - (uint32_t)&__data_start__);
    uint8_t btn_oldstate = 0;
    uint32_t read_addr = 0;
    uint32_t erase_addr = 0;
    uint8_t data[256];
    int32_t x, y, z;

    // Initialize 115200 8N1 UART on pads 44/45 for printf and output banner:
    uart_init();
    printf("\n\n\n\n");
    printf("SparkFun QuickLogic Thing Plus - EOS S3 MCU + eFPGA Bare-Bones Demo\n");
    printf("https://github.com/s-holst/EOS-S3-QTplus\n");
    printf("ROM image size: %d (0x%x) bytes\n", rom_bytes, rom_bytes);

    // Set up and verify flash chip communication:
    spi_init();
    tFlashBootHeader header;
    printf("Flash ID: %x\n", spi_flash_read_id());
    spi_flash_read(0x120, (uint8_t *)&header, sizeof(header));
    printf("CfgSM boot header at 0x120: id=%x ", header.id);
    if (header.id == 0x20)
        printf("speed=%d size=%dkiBytes\n", header.baudr_mult, (1 + header.dwords) * 8 / 1024);
    else
        printf("<invalid>\n");

    i2c_accel_init();
    io_init();

    printf("\nPress <space> for help.\n");

    while (1)
    {
        // Flash green LED every 1.024s:
        io_set_green(!(uptime_ms & 0x3ff));

        // Report USR button state changes:
        uint8_t btn_state = io_get_usrbtn();
        if (btn_state != btn_oldstate)
        {
            if (btn_state)
                printf("USR button pressed\n");
            else
                printf("USR button released\n");
            btn_oldstate = btn_state;
        }

        // Process commands from UART:
        if (uart_rx_available())
        {
            switch (uart_rx() & 0xff)
            {
            case 'a':
                i2c_accel_read(&x, &y, &z);
                printf("X %6d Y %6d Z %6d BAT %d uptime %d\n", x, y, z, io_adc_read(), uptime_ms);
                break;
            case 'r':
                spi_flash_read(read_addr, data, 256);
                for (int i = 0; i < 256; i += 16)
                {
                    printf("%06x", i + read_addr);
                    for (int j = 0; j < 16; j++)
                        printf(" %02x", data[i + j]);
                    printf("\n");
                }
                read_addr += 256;
                break;
            case 'e':
                printf("Erase a 4096-byte sector starting at 0x%x ?\n", erase_addr);
                printf("<y> - Yes\n<any other key> - Abort.\n");
                io_set_green(1);
                io_set_red(1);
                if ((uart_rx() & 0xff) == 'y')
                {
                    io_set_green(0);
                    printf("Erasing...\n");
                    spi_flash_erase_sector(erase_addr);
                    printf("Done.\n");
                    erase_addr += 4096;
                }
                else
                    printf("Aborted.\n");
                io_set_red(0);
                break;
            case 'f':
                printf("Write currently loaded image (%d bytes) to flash?\n", rom_bytes);
                printf("<y> - Yes\n<any other key> - Abort.\n");
                io_set_green(1);
                io_set_red(1);
                if ((uart_rx() & 0xff) == 'y')
                {
                    printf("Writing...  ('*'=sector erase, '.'=page prog. success, 'E'=page prog. error)\n");
                    io_set_green(0);
                    for (int sector_offset = 0; sector_offset < rom_bytes; sector_offset += 4096)
                    {
                        uint32_t sector_bytes = MIN(4096, rom_bytes - sector_offset);
                        printf("*");
                        spi_flash_erase_sector(sector_offset);
                        for (int page_offset = 0; page_offset < sector_bytes; page_offset += 256)
                        {
                            uint32_t addr = sector_offset + page_offset;
                            uint8_t *data = (uint8_t *)(addr);
                            if (spi_flash_program_and_verify_page(addr, data, MIN(256, rom_bytes - addr)))
                                printf("E");
                            else
                                printf(".");
                        }
                        printf("\n");
                    }
                    printf("Done.\n");
                }
                else
                    printf("Aborted.\n");
                io_set_red(0);
                break;
            default:
                printf("<a> - read accelerometer and battery ADC.\n");
                printf("<r> - read one page of flash memory.\n");
                printf("<e> - erase a sector of flash memory.\n");
                printf("<f> - flash currently loaded image.\n");
                printf("<any other key> - print this message.\n\n");
                break;
            }
        }
    }

    return 0;
}