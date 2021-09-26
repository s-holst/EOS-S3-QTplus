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

#ifndef __REGS_SPI_H
#define __REGS_SPI_H

#include <stdint.h>

#define SPI ((SPI_typedef *)0x40007000)

/* Registers for SPI master (aka SPI 1 master, SPIm), the one connected to flash memory.
   EOS3 also has a second SPI master block (aka, SPI 0 master, SPI sensor) connected to FFE via WB. */

typedef struct
{
    /* 0x00 Control Register 0
       [20:16]+1 = Data Frame Size (bits) for 32-bit mode (used when SSI_MAX_XFER_SIZE is configured to 32). 3(4bits)..15(16bits) <0>
       [15:12]+1 = Control Frame Size (bits) for Microwire. <0(1bit)>..15(16bits)
       [11] Shift Register Loopback, used for testing. <0=disable> 1=loopback
       [10] Ignored for SPI master
       [9:8] Transfer Mode (affects FIFO) <0=Tx&Rx> 1=TxOnly 2=RxOnly 3=EEPROM
       [7] CLK Inactive Polarity <0=low> 1=high
       [6] CLK Phase <0=data valid at 1st edge> 1=data valid at 2nd edge
       [5:4] SPI Flavor <0=Motorola SPI> only
       [3:0]+1 = Data Frame Size (bits) for non-32-bit mode. 3(4bits)..15(16bits) <7(8bits)>
       */
    volatile uint32_t CTRLR0;
    volatile uint32_t CTRLR1;           // 0x04 [15:0]+1 = Number of Data Frames for transfer modes RxOnly and EEPROM
    volatile uint32_t SSIENR;           // 0x08 [0] SPI master <0=disable> 1=enable, must disable to access CTRLR0 CTRLR1 BAUDR, must enable to access DR0
    volatile uint32_t reserved1;        //
    volatile uint32_t SER;              // 0x10 [2:0] Slave Select (3 SSlines) 1=asserts the corresponding slave select line at transfer start
    volatile uint32_t BAUDR;            // 0x14 Baud Rate = C02Hz/[15:0], must be even ([0]=0), should be >=2, rate should be <=5MHz, <0>
    volatile uint32_t TXFTLR;           // 0x18 Tx FIFO Threshold
    volatile uint32_t RXFTLR;           // 0x1C Rx FIFO Threshold
    volatile uint32_t TXFLR;            // 0x20 Tx FIFO Level
    volatile uint32_t RXFLR;            // 0x24 Rx FIFO Level
    volatile uint32_t SR;               // 0x28 Status [0]R busy [1]R TxFIFO not full [2]R TxFIFO empty [3]R RxFIFO not empty [4]R RxFIFO full [5]RC ignore [6]RC data collision error
    volatile uint32_t IMR;              // 0x2C Interrupt Mas
    volatile uint32_t ISR;              // 0x30 Interrupt Status
    volatile uint32_t RISR;             // 0x34 Interrupt Raw Status
    volatile uint32_t TXOICR;           // 0x38 Tx FIFO Overflow Interrupt Clear
    volatile uint32_t RXOICR;           // 0x3C Rx FIFO Overflow Interrupt Clear
    volatile uint32_t RXUICR;           // 0x40 Rx FIFO Underflow Interrupt Clear
    volatile uint32_t MSTICR;           // 0x44 Multi-Master Contention Interrupt Clear
    volatile uint32_t ICR;              // 0x48 Interrupt Clear
    volatile uint32_t reserved2[3];     //
    volatile uint32_t IDR;              //
    volatile uint32_t SSI_COMP_VERSION; //
    volatile uint32_t DR0;              // 0x60 Data
} SPI_typedef;

#define SPI_CTRLR0_CLK_IDLE_POL_HIGH 0x80
#define SPI_CTRLR0_CLK_PHASE_2EDGE 0x40
#define SPI_CTRLR0_DATA_FRAME_SIZE(x) ((x)-1)
#define SPI_CTRLR0_CTRL_FRAME_SIZE(x) (((x)-1) << 12)
#define SPI_CTRLR0_CTRL_FRAME_SIZE32(x) (((x)-1) << 16)
#define SPI_CTRLR0_TMOD_TX (1 << 8)
#define SPI_CTRLR0_TMOD_RX (2 << 8)
#define SPI_CTRLR0_TMOD_EEPROM (3 << 8)

#define SPI_SR_BUSY 0x01
#define SPI_SR_TFNF 0x02
#define SPI_SR_TFE 0x04
#define SPI_SR_RFNE 0x08
#define SPI_SR_RFF 0x10
#define SPI_SR_DCOL 0x40

#endif