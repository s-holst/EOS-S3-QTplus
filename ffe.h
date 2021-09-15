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

#ifndef __FFE_H
#define __FFE_H

#include <stdint.h>


typedef struct
{
	volatile uint32_t ADDR;			/* 0x000 */
	volatile uint32_t WDATA;			/* 0x004 */
	volatile uint32_t CSR;				/* 0x008 */
	volatile uint32_t RDATA;			/* 0x00C */
	volatile uint32_t reserved0[1];		/* 0x010 */
	volatile uint32_t SRAM_TEST_REG1;		/* 0x014 */
	volatile uint32_t SRAM_TEST_REG2;		/* 0x018 */
	volatile uint32_t reserved1[1];		/* 0x01C */
	volatile uint32_t FFE_CSR;			/* 0x020 */
	volatile uint32_t reserved2[5];		/* 0x024 */
	volatile uint32_t FFE_DBG_COMBINED;		/* 0x038 */
	volatile uint32_t reserved3[49];		/* 0x03C */
	volatile uint32_t CMD;			/* 0x100 */
	volatile uint32_t reserved4[1];		/* 0x104 */
	volatile uint32_t INTERRUPT;		/* 0x108 */
	volatile uint32_t INTERRUPT_EN;		/* 0x10C */
	volatile uint32_t STATUS;			/* 0x110 */
	volatile uint32_t MAILBOX_TO_FFE0;		/* 0x114 */
	volatile uint32_t reserved5[2];		/* 0x118 */
	volatile uint32_t SM_RUNTIME_ADDR;		/* 0x120 */
	volatile uint32_t SM0_RUNTIME_ADDR_CTRL;	/* 0x124 */
	volatile uint32_t SM1_RUNTIME_ADDR_CTRL;	/* 0x128 */
	volatile uint32_t SM0_RUNTIME_ADDR_CUR;	/* 0x12C */
	volatile uint32_t SM1_RUNTIME_ADDR_CUR;	/* 0x130 */
	volatile uint32_t reserved6[3];		/* 0x134 */
	volatile uint32_t SM0_DEBUG_SEL;		/* 0x140 */
	volatile uint32_t SM1_DEBUG_SEL;		/* 0x144 */
	volatile uint32_t FFE_DEBUG_SEL;		/* 0x148 */
	volatile uint32_t reserved7[1];		/* 0x14C */
	volatile uint32_t FFE0_BREAK_POINT_CFG;	/* 0x150 */
	volatile uint32_t FFE0_BREAK_POINT_CONT;	/* 0x154 */
	volatile uint32_t FFE0_BREAK_POINT_STAT;	/* 0x158 */
	volatile uint32_t reserved8[1];		/* 0x15C */
	volatile uint32_t FFE0_BP_XPC_0;		/* 0x160 */
	volatile uint32_t FFE0_BP_XPC_1;		/* 0x164 */
	volatile uint32_t FFE0_BP_XPC_2;		/* 0x168 */
	volatile uint32_t FFE0_BP_XPC_3;		/* 0x16C */
} FFE_typedef;

#define FFE_BASE (0x4004A000)
#define FFE ((FFE_typedef*) FFE_BASE)

#define FFE_CSR_MASTER_START         ((uint8_t)0x01)
#define FFE_CSR_MASTER_WR_EN         ((uint8_t)0x02)
#define FFE_CSR_MUX_WB_SM            ((uint8_t)0x04)
#define FFE_CSR_BUSY                 ((uint8_t)0x08)
#define FFE_CSR_OVFL                 ((uint8_t)0x10)
#define FFE_CSR_I2C0MUX_SEL_WBMASTER ((uint8_t)0x20)


#define WB_I2C_PRELO  0  // pre-scaler low byte
#define WB_I2C_PREHI  1  // pre-scaler high byte
#define WB_I2C_MCR    2  // Main control register
#define WB_I2C_TXRX   3  // Data I/O register
#define WB_I2C_CSR    4  // Command and status register

#define WB_I2C_MCR_EN_Msk   0x80
#define WB_I2C_MCR_IEN_Msk  0x40

#define WB_I2C_CSR_IACK_Msk   0x01
#define WB_I2C_CSR_NACK_Msk   0x08
#define WB_I2C_CSR_WRITE_Msk  0x10
#define WB_I2C_CSR_READ_Msk   0x20
#define WB_I2C_CSR_STOP_Msk   0x40
#define WB_I2C_CSR_START_Msk  0x80

#define WB_I2C_CSR_IF_Msk     0x01
#define WB_I2C_CSR_TIP_Msk    0x02
#define WB_I2C_CSR_AL_Msk     0x20
#define WB_I2C_CSR_BUSY_Msk   0x40
#define WB_I2C_CSR_RXACK_Msk  0x80


#endif