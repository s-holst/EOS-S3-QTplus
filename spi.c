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

#include "regs/iomux.h"
#include "regs/spi.h"

int spi_init()
{
    IOMUX->PAD[34] = IOMUX_PAD_34_FSEL_SPIm_CLK | IOMUX_PAD_E_4MA;
    IOMUX->PAD[38] = IOMUX_PAD_38_FSEL_SPIm_MOSI | IOMUX_PAD_E_4MA;
    IOMUX->PAD[39] = IOMUX_PAD_39_FSEL_SPIm_SSn1 | IOMUX_PAD_E_4MA;
    //IOMUX->PAD[25] = IOMUX_PAD_25_FSEL_SPIm_SSn3 | IOMUX_PAD_E_4MA;

    IOMUX->PAD[36] = IOMUX_PAD_36_FSEL_SPIm_MISO | IOMUX_PAD_OEN_DISABLE | IOMUX_PAD_REN_ENABLE;
    IOMUX->SPIm_MISO_SEL = IOMUX_SPIm_MISO_SEL_PAD36;

    SPI->SSIENR = 0; // disable chip
    SPI->BAUDR = 8;  // SPI master clock = 4.5 MHz (divBy8, Source:C02)
    SPI->SER = 0;
    SPI->SSIENR = 1;

    return 0;
}

int spi_txrx(uint8_t ucChipMsk, uint8_t *pucTxData, const uint32_t uiTxLen, uint8_t *pucRxData, const uint32_t uiRxLen)
{
    // configure transfer
    SPI->SSIENR = 0;
    if (uiRxLen > 0)
    {
        SPI->CTRLR0 = SPI_CTRLR0_TMOD_EEPROM | SPI_CTRLR0_DATA_FRAME_SIZE(8);
        SPI->CTRLR1 = uiRxLen - 1; // number of response frames
    }
    else
    {
        SPI->CTRLR0 = SPI_CTRLR0_TMOD_TX | SPI_CTRLR0_DATA_FRAME_SIZE(8);
        SPI->CTRLR1 = 0; // no response frames, just transmit
    }
    SPI->SSIENR = 1;

    for (int i = 0; i < uiTxLen; i++)
    {
        while (!(SPI->SR & SPI_SR_TFNF))
            SPI->SER = ucChipMsk; // Start transmitting, if FIFO is full.
        SPI->DR0 = pucTxData[i];
    }

    SPI->SER = ucChipMsk; // Ensure transmission has started.

    // Wait for all response frames.
    for (int i = 0; i < uiRxLen; i++)
    {
        while (!(SPI->SR & SPI_SR_RFNE))
            ;
        pucRxData[i] = SPI->DR0;
    }

    // Wait until idle before releasing #CS.
    // Important when there are no response frames.
    while (SPI->SR & SPI_SR_BUSY)
        ;

    SPI->SER = 0;

    return 0;
}

uint32_t spi_flash_read_id()
{
    uint32_t id = 0;
    uint8_t cmd = 0x9F;
    spi_txrx(1, &cmd, 1, (uint8_t *)&id, 3);
    return id;
}

void spi_flash_write_enable()
{
    uint8_t cmd = 0x06;
    spi_txrx(1, &cmd, 1, NULL, 0);
}

uint16_t spi_flash_read_status()
{
    uint16_t status;
    uint8_t cmd = 0x05; // read lower 8 bits
    spi_txrx(1, &cmd, 1, (uint8_t *)&status, 1);
    cmd = 0x35; // read upper 8 bits
    spi_txrx(1, &cmd, 1, ((uint8_t *)&status) + 1, 1);
    return status;
}

void spi_flash_read(uint32_t uiAddr, uint8_t *pucData, const uint32_t uiLen)
{
    uint8_t cmd[4];
    cmd[0] = 0x03;
    cmd[1] = (uiAddr >> 16) & 0xff;
    cmd[2] = (uiAddr >> 8) & 0xff;
    cmd[3] = uiAddr & 0xff;
    spi_txrx(1, cmd, 4, pucData, uiLen);
}

void spi_flash_wait_write_completion()
{
    uint8_t status;
    uint8_t cmd = 0x05;
    do
    {
        spi_txrx(1, &cmd, 1, &status, 1);
    } while (status & 0x01); // check WIP bit
}

/* Erases 4096-byte sector that contains given uiAddr. */
void spi_flash_erase_sector(uint32_t uiAddr)
{
    uint8_t cmd[4];
    cmd[0] = 0x20;
    cmd[1] = (uiAddr >> 16) & 0xff;
    cmd[2] = (uiAddr >> 8) & 0xff;
    cmd[3] = uiAddr & 0xff;

    spi_flash_write_enable();
    spi_txrx(1, cmd, 4, NULL, 0);
    spi_flash_wait_write_completion();
}

/* Programs a single 256-byte page.
   Maximum data length is 256.
   Can only program bits to 0.
   Use 'erase' functions to reset bits to 1.
   Caution: Address will warp around and verification will fail when trying
   to program across page boundaries.
   
   returns -2 if verification failed. */
int spi_flash_program_and_verify_page(uint32_t uiAddr, uint8_t *pucData, const uint32_t uiLen)
{
    if (uiLen > 256)
        return -1;

    uint8_t buf[256 + 4];
    buf[0] = 0x02;
    buf[1] = (uiAddr >> 16) & 0xff;
    buf[2] = (uiAddr >> 8) & 0xff;
    buf[3] = uiAddr & 0xff;
    for (int i = 0; i < uiLen; i++)
        buf[i + 4] = pucData[i];

    spi_flash_write_enable();
    spi_txrx(1, buf, uiLen + 4, NULL, 0);
    spi_flash_wait_write_completion();

    spi_flash_read(uiAddr, buf, uiLen);
    for (int i = 0; i < uiLen; i++)
        if (buf[i] != pucData[i])
            return -2;

    return 0;
}