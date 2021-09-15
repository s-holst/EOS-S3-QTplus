/* Copyright 2021 Stefan Holst

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   ---------------------------------------------------------------------------*/
   
#ifndef __UART_H
#define __UART_H

#include <stdint.h>

typedef struct
{
	volatile uint32_t UART_DR;		/* Data Address: 0x00 */
	volatile uint32_t UART_RSR;         /* Receive Status Register: 0x04 */
	volatile uint32_t reserved1[4];		/* Reserved: 0x08 - 0x14 */
	volatile uint32_t UART_TFR;		/* Flag Register 0x18 */
	volatile uint32_t reserved2[1];         /* Reserved 0x1C */
	volatile uint32_t UART_ILPR;        /* IrDA Low Power Counter Register 0x20 */
	volatile uint32_t UART_IBRD;        // 0x024 [15:0] = int(C11Hz/baudrate/16)
	volatile uint32_t UART_FBRD;        // 0x028 [5:0] = int(((C11Hz/baudrate/16)%1)*64+0.5)
	volatile uint32_t UART_LCR_H;       /* Line Control Register 0x2C */
	volatile uint32_t UART_CR;          /* Control Register 0x30 */
	volatile uint32_t UART_IFLS;        /* Interrupt FIFO Level Select Register 0x34 */
	volatile uint32_t UART_IMSC;        /* Interrupt Mask Set/Clear Register 0x38 */
	volatile uint32_t UART_RIS;         /* Raw Interrupt Status Register 0x3C */
	volatile uint32_t UART_MIS;         /* Masked Interrupt Status Register 0x40 */
	volatile uint32_t UART_ICR;         // 0x044 Interrupt Clear Register [10:0] writing 1 clears
	volatile uint32_t reserved4[14];
	volatile uint32_t UART_TCR;       /* Test Control Register 0x48 */
	volatile uint32_t UART_ITIP;
	volatile uint32_t UART_ITOP;
	volatile uint32_t UART_TDR;
	volatile uint32_t reserved3[980];       /* Reserved 0x4c - 0cFDC */
	volatile uint32_t UART_PeriphID0;   /* Peri. ID0 Register (0x11)                  Address offset: 0xFE0 */
	volatile uint32_t UART_PeriphID1;   /* Peri. ID1 Register (0x10)                  Address offset: 0xFE4 */
	volatile uint32_t UART_PeriphID2;   /* Peri. ID2 Register                         Address offset: 0xFE8 */
	volatile uint32_t UART_PeriphID3;   /* Peri. ID3 Register (0x00)                  Address offset: 0xFEC */
	volatile uint32_t UART_CellID0;     /* Cell ID0 Register  (0x0D)                  Address offset: 0xFF0 */
	volatile uint32_t UART_CellID1;     /* Cell ID1 Register  (0xF0)                  Address offset: 0xFF4 */
	volatile uint32_t UART_CellID2;     /* Cell ID2 Register  (0x05)                  Address offset: 0xFF8 */
	volatile uint32_t UART_CellID3;     /* Cell ID3 Register  (0xB1)                  Address offset: 0xFFC */
} UART_typedef;

#define UART_BASE (0x40010000)
#define UART ((UART_typedef*) UART_BASE)

/* Bit definition for data register */
#define UART_DR_OVERRUN_ERR				  	  ((uint32_t) (1 << 11))
#define UART_DR_BREAK_ERR                     ((uint32_t) (1 << 10))
#define UART_DR_PARITY_ERR                    ((uint32_t) (1 << 9))
#define UART_DR_FRAMING_ERR                   ((uint32_t) (1 << 8))
#define UART_DR_DATA                          ((uint32_t) (0xFF))

/* Bit definition for rx status register */
#define UART_RSR_OVERRUN_ERR                  ((uint32_t) (1 << 3))
#define UART_RSR_BREAK_ERR                    ((uint32_t) (1 << 2))
#define UART_RSR_PARITY_ERR                   ((uint32_t) (1 << 1))
#define UART_RSR_FRAMING_ERR                  ((uint32_t) (1 << 0))

/* Bit definition for flag register */
#define UART_TFR_RING_INDICATOR               ((uint32_t) (1 << 8))
#define UART_TFR_TX_FIFO_EMPTY                ((uint32_t) (1 << 7))
#define UART_TFR_RX_FIFO_FULL                 ((uint32_t) (1 << 6))
#define UART_TFR_TX_FIFO_FULL                 ((uint32_t) (1 << 5))
#define UART_TFR_RX_FIFO_EMPTY                ((uint32_t) (1 << 4))
#define UART_TFR_BUSY                         ((uint32_t) (1 << 3))
#define UART_TFR_DATA_CARRY_DETECT            ((uint32_t) (1 << 2))
#define UART_TFR_DATA_SET_RDY                 ((uint32_t) (1 << 1))
#define UART_TFR_CLEAR_TO_SEND                ((uint32_t) (1 << 0))

/* Bit definition for IrDA low power counter register */
#define UART_ILPR_LOW_POWER_DIVISOR           ((uint32_t) (0xFF))

/* Bit definition for integer baud rate register */
#define UART_IBRD_BAUD_INT_DIVISOR            ((uint32_t) (0xFFFF))


/* Bit definition for fractional baud rate register */
#define UART_IBRD_BAUD_FRACT_DIVISOR          ((uint32_t) (0x1F))

/* Bit definition for line control register */
#define UART_LCR_STICK_PARITY_SELECT          ((uint32_t) (0x80))
#define UART_LCR_WLEN_8_BITS                  ((uint32_t) (0x60))
#define UART_LCR_WLEN_7_BITS                  ((uint32_t) (0x40))
#define UART_LCR_WLEN_6_BITS                  ((uint32_t) (0x20))
#define UART_LCR_WLEN_5_BITS                  ((uint32_t) (0x00))
#define UART_LCR_ENABLE_FIFO                  ((uint32_t) (0x10))
#define UART_LCR_TWO_STOP_BITS                ((uint32_t) (0x08))
#define UART_LCR_EVEN_PARITY                  ((uint32_t) (0x04))
#define UART_LCR_ODD_PARITY                   ((uint32_t) (0x00))
#define UART_LCR_PARITY_ENABLE                ((uint32_t) (0x02))
#define UART_LCR_SEND_BREAK                   ((uint32_t) (0x01))

/* Bit definition for control register */
#define UART_CR_CTS_ENABLE	                  ((uint32_t) (0x8000))
#define UART_CR_RTS_ENABLE	                  ((uint32_t) (0x4000))
#define UART_CR_OUT2	                      ((uint32_t) (0x2000))
#define UART_CR_OUT1	                      ((uint32_t) (0x1000))
#define UART_CR_RTS	                          ((uint32_t) (0x0800))
#define UART_CR_DTR  	                      ((uint32_t) (0x0400))
#define UART_CR_RX_ENABLE                     ((uint32_t) (0x0200))
#define UART_CR_TX_ENABLE                     ((uint32_t) (0x0100))
#define UART_CR_LOOPBACK_ENABLE               ((uint32_t) (0x0080))
#define UART_CR_SIR_LOWPOWER                  ((uint32_t) (0x0004))
#define UART_CR_SIR_ENABLE                    ((uint32_t) (0x0002))
#define UART_CR_UART_ENABLE                   ((uint32_t) (0x0001))

/* Bit definition for interrupt FIFO level select register */
#define UART_IFLS_RX_1_8_FULL                 ((uint32_t) (0x0000))
#define UART_IFLS_RX_1_4_FULL                 ((uint32_t) (0x0008))
#define UART_IFLS_RX_1_2_FULL                 ((uint32_t) (0x0010))
#define UART_IFLS_RX_3_4_FULL                 ((uint32_t) (0x0018))
#define UART_IFLS_RX_7_8_FULL                 ((uint32_t) (0x0020))
#define UART_IFLS_TX_1_8_FULL                 ((uint32_t) (0x0000))
#define UART_IFLS_TX_1_4_FULL                 ((uint32_t) (0x0001))
#define UART_IFLS_TX_1_2_FULL                 ((uint32_t) (0x0002))
#define UART_IFLS_TX_3_4_FULL                 ((uint32_t) (0x0003))
#define UART_IFLS_TX_7_8_FULL                 ((uint32_t) (0x0004))

/* Bit definition for interrupt mask set/clear register */
#define UART_IMSC_OVERRUN_ERR                 ((uint32_t) (0x0400))
#define UART_IMSC_BREAK_ERR                   ((uint32_t) (0x0200))
#define UART_IMSC_PARITY_ERR                  ((uint32_t) (0x0100))
#define UART_IMSC_FRAMING_ERR                 ((uint32_t) (0x0080))
#define UART_IMSC_RX_TIMEOUT                  ((uint32_t) (0x0040))
#define UART_IMSC_TX                          ((uint32_t) (0x0020))
#define UART_IMSC_RX                          ((uint32_t) (0x0010))
#define UART_IMSC_DSR                         ((uint32_t) (0x0008))
#define UART_IMSC_DCD                         ((uint32_t) (0x0004))
#define UART_IMSC_CTS                         ((uint32_t) (0x0002))
#define UART_IMSC_RI                          ((uint32_t) (0x0001))

/* Bit definition for raw interrupt status register */
#define UART_RIS_OVERRUN_ERR                  ((uint32_t) (0x0400))
#define UART_RIS_BREAK_ERR                    ((uint32_t) (0x0200))
#define UART_RIS_PARITY_ERR                   ((uint32_t) (0x0100))
#define UART_RIS_FRAMING_ERR                  ((uint32_t) (0x0080))
#define UART_RIS_RX_TIMEOUT                   ((uint32_t) (0x0040))
#define UART_RIS_TX                           ((uint32_t) (0x0020))
#define UART_RIS_RX                           ((uint32_t) (0x0010))
#define UART_RIS_DSR                          ((uint32_t) (0x0008))
#define UART_RIS_DCD                          ((uint32_t) (0x0004))
#define UART_RIS_CTS                          ((uint32_t) (0x0002))
#define UART_RIS_RI                           ((uint32_t) (0x0001))

/* Bit definition for masked interrupt status register */
#define UART_MIS_OVERRUN_ERR                  ((uint32_t) (0x0400))
#define UART_MIS_BREAK_ERR                    ((uint32_t) (0x0200))
#define UART_MIS_PARITY_ERR                   ((uint32_t) (0x0100))
#define UART_MIS_FRAMING_ERR                  ((uint32_t) (0x0080))
#define UART_MIS_RX_TIMEOUT                   ((uint32_t) (0x0040))
#define UART_MIS_TX                           ((uint32_t) (0x0020))
#define UART_MIS_RX                           ((uint32_t) (0x0010))
#define UART_MIS_DSR                          ((uint32_t) (0x0008))
#define UART_MIS_DCD                          ((uint32_t) (0x0004))
#define UART_MIS_CTS                          ((uint32_t) (0x0002))
#define UART_MIS_RI                           ((uint32_t) (0x0001))

/* Bit definition for interrupt clear register */
#define UART_IC_OVERRUN_ERR                  ((uint32_t) (0x0400))
#define UART_IC_BREAK_ERR                    ((uint32_t) (0x0200))
#define UART_IC_PARITY_ERR                   ((uint32_t) (0x0100))
#define UART_IC_FRAMING_ERR                  ((uint32_t) (0x0080))
#define UART_IC_RX_TIMEOUT                   ((uint32_t) (0x0040))
#define UART_IC_TX                           ((uint32_t) (0x0020))
#define UART_IC_RX                           ((uint32_t) (0x0010))
#define UART_IC_DSR                          ((uint32_t) (0x0008))
#define UART_IC_DCD                          ((uint32_t) (0x0004))
#define UART_IC_CTS                          ((uint32_t) (0x0002))
#define UART_IC_RI                           ((uint32_t) (0x0001))

/* Bit definition for dma control register */
#define UART_DMACR_ON_ERR                    ((uint32_t) (0x0004))
#define UART_DMACR_TX_DMA_ENABLE             ((uint32_t) (0x0002))
#define UART_DMACR_RX_DMA_ENABLE             ((uint32_t) (0x0001))

#endif