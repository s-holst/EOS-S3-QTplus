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

#ifndef __DMA_H
#define __DMA_H

#include <stdint.h>

#define DMA ((DMA_typedef *)0x40007400)

typedef struct
{
    volatile uint32_t DMA_CTRL;         // 0x00 DMA Control Register
    volatile uint32_t DMA_DEST_ADDR;    // 0x04 DMA Destination Address
    volatile uint32_t DMA_XFER_CNT;     // 0x08 DMA Transfer Count
    volatile uint32_t CFG_FLASH_HEADER; // 0x0C CFG FLASH Header
    volatile uint32_t DMA_INTR;         // 0x10 DMA Interrupt Register
    volatile uint32_t DMA_INTR_MASK;    // 0x14 DMA Interrupt Mask Register
} DMA_typedef;

#define DMA_CTRL_START_Msk 0x1
#define DMA_CTRL_STOP_Msk 0x2
#define DMA_CTRL_AHB_SEL_Msk 0x4

#endif