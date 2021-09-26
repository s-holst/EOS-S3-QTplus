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

#ifndef __REGS_UART_H
#define __REGS_UART_H

#include <stdint.h>

#define UART ((UART_typedef *)0x40010000)

typedef struct
{
    volatile uint32_t DR;  // 0x000 Data
    volatile uint32_t RSR; // 0x004 Receive Status
    volatile uint32_t reserved008[4];
    /* 0x018 Flags
       [8]R RI Ring Indicator
       [7]R TXFE 1=Transmit FIFO empty
       [6]R RXFF 1=Receive FIFO full
       [5]R TXFF 1=Transmit FIFO full
       [4]R RXFE 1=Receive FIFO empty
       [3]R BUSY 1=UART is busy sending data
       [2]R DCD Data Carrier Detect (inverted)
       [1]R DSR Data Send Ready (inverted)
       [0]R CTS Clear To Send (inverted) */
    volatile uint32_t TFR;
    volatile uint32_t reserved201C;     //
    volatile uint32_t ILPR;             // 0x020 IrDA Low Power Counter
    volatile uint32_t IBRD;             // 0x024 [15:0] = int(C11Hz/baudrate/16)
    volatile uint32_t FBRD;             // 0x028 [5:0] = int(((C11Hz/baudrate/16)%1)*64+0.5)
    volatile uint32_t LCR_H;            // 0x02C Line Control
    volatile uint32_t CR;               // 0x030 Control
    volatile uint32_t IFLS;             // 0x034 Interrupt FIFO Level Select
    volatile uint32_t IMSC;             // 0x038 [10:0] Interrupt Mask Set/Clear, see: UART_intr_*_Msk
    volatile uint32_t RIS;              // 0x03C [10:0] Raw Interrupt Status, see: UART_intr_*_Msk
    volatile uint32_t MIS;              // 0x040 [10:0] Masked Interrupt Status, see: UART_intr_*_Msk
    volatile uint32_t ICR;              // 0x044 [10:0]W1C interrupt clear, see: UART_intr_*_Msk
    volatile uint32_t reserved048[14];  //
    volatile uint32_t TCR;              // 0x080 Test Control
    volatile uint32_t ITIP;             // 0x084
    volatile uint32_t ITOP;             // 0x088
    volatile uint32_t TDR;              // 0x08C
    volatile uint32_t reserved090[980]; //
    volatile uint32_t PeriphID0;        // 0xFE0 Peri. ID0 <0x11>
    volatile uint32_t PeriphID1;        // 0xFE4 Peri. ID1 <0x10>
    volatile uint32_t PeriphID2;        // 0xFE8 Peri. ID2 <0x34>
    volatile uint32_t PeriphID3;        // 0xFEC Peri. ID3 <0x00>
    volatile uint32_t CellID0;          // 0xFF0 Cell ID0 <0x0D>
    volatile uint32_t CellID1;          // 0xFF4 Cell ID1 <0xF0>
    volatile uint32_t CellID2;          // 0xFF8 Cell ID2 <0x05>
    volatile uint32_t CellID3;          // 0xFFC Cell ID3 <0xB1>
} UART_typedef;

#define UART_DR_DATA_Msk 0x0FF
#define UART_DR_FRAMING_ERR_Msk 0x100
#define UART_DR_PARITY_ERR_Msk 0x200
#define UART_DR_BREAK_ERR_Msk 0x400
#define UART_DR_OVERRUN_ERR_Msk 0x800

#define UART_RSR_OVERRUN_ERR 0x08
#define UART_RSR_BREAK_ERR 0x04
#define UART_RSR_PARITY_ERR 0x02
#define UART_RSR_FRAMING_ERR 0x01

#define UART_TFR_RING_INDICATOR 0x100
#define UART_TFR_TX_FIFO_EMPTY 0x080
#define UART_TFR_RX_FIFO_FULL 0x040
#define UART_TFR_TX_FIFO_FULL 0x020
#define UART_TFR_RX_FIFO_EMPTY 0x010
#define UART_TFR_BUSY 0x008
#define UART_TFR_DATA_CARRY_DETECT 0x004
#define UART_TFR_DATA_SET_RDY 0x002
#define UART_TFR_CLEAR_TO_SEND 0x001

#define UART_LCR_STICK_PARITY_SELECT 0x80
#define UART_LCR_WLEN_8_BITS 0x60
#define UART_LCR_WLEN_7_BITS 0x40
#define UART_LCR_WLEN_6_BITS 0x20
#define UART_LCR_WLEN_5_BITS 0x00
#define UART_LCR_ENABLE_FIFO 0x10
#define UART_LCR_TWO_STOP_BITS 0x08
#define UART_LCR_EVEN_PARITY 0x04
#define UART_LCR_ODD_PARITY 0x00
#define UART_LCR_PARITY_ENABLE 0x02
#define UART_LCR_SEND_BREAK 0x01

#define UART_CR_CTS_ENABLE 0x8000
#define UART_CR_RTS_ENABLE 0x4000
#define UART_CR_OUT2 0x2000
#define UART_CR_OUT1 0x1000
#define UART_CR_RTS 0x0800
#define UART_CR_DTR 0x0400
#define UART_CR_RX_ENABLE 0x0200
#define UART_CR_TX_ENABLE 0x0100
#define UART_CR_LOOPBACK_ENABLE 0x0080
#define UART_CR_SIR_LOWPOWER 0x0004
#define UART_CR_SIR_ENABLE 0x0002
#define UART_CR_UART_ENABLE 0x0001

#define UART_IFLS_RX_1_8_FULL 0x0000
#define UART_IFLS_RX_1_4_FULL 0x0008
#define UART_IFLS_RX_1_2_FULL 0x0010
#define UART_IFLS_RX_3_4_FULL 0x0018
#define UART_IFLS_RX_7_8_FULL 0x0020
#define UART_IFLS_TX_1_8_FULL 0x0000
#define UART_IFLS_TX_1_4_FULL 0x0001
#define UART_IFLS_TX_1_2_FULL 0x0002
#define UART_IFLS_TX_3_4_FULL 0x0003
#define UART_IFLS_TX_7_8_FULL 0x0004

#define UART_intr_OVERRUN_ERR_Msk 0x0400
#define UART_intr_BREAK_ERR_Msk 0x0200
#define UART_intr_PARITY_ERR_Msk 0x0100
#define UART_intr_FRAMING_ERR_Msk 0x0080
#define UART_intr_RX_TIMEOUT_Msk 0x0040
#define UART_intr_TX_Msk 0x0020
#define UART_intr_RX_Msk 0x0010
#define UART_intr_DSR_Msk 0x0008
#define UART_intr_DCD_Msk 0x0004
#define UART_intr_CTS_Msk 0x0002
#define UART_intr_RI_Msk 0x0001
#define UART_intr_ALL_Msk 0x07FF

#endif