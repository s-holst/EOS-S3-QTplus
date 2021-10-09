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

#ifndef __SPI_H
#define __SPI_H

#include <stdint.h>

int spi_init();
int spi_tx(const uint8_t ucChipMsk, const uint8_t *pucTxData, const uint32_t uiTxLen);
int spi_rx(const uint8_t ucChipMsk, uint8_t *pucRxData, const uint32_t uiRxLen);
int spi_cmd(const uint8_t ucChipMsk, const uint8_t *pucTxData, const uint32_t uiTxLen, uint8_t *pucRxData, const uint32_t uiRxLen);
int spi_txrx(const uint8_t ucChipMsk, const uint8_t *pucTxData, uint8_t *pucRxData, const uint32_t uiLen);

uint32_t spi_flash_read_id();
uint16_t spi_flash_read_status();
void spi_flash_read(uint32_t uiAddr, uint8_t *pucData, const uint32_t uiLen);
void spi_flash_erase_sector(uint32_t uiAddr);
int spi_flash_program_and_verify_page(uint32_t uiAddr, uint8_t *pucData, const uint32_t uiLen);

#endif