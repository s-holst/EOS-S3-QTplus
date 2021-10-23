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

#ifndef __REGS_PKFB_H
#define __REGS_PKFB_H

#include <stdint.h>

#define PKFB ((PKFB_typedef *)0x40002000)

/*
   PF0: capacity: 256 x 32 bit
   PF1: capacity: 128 x 32 bit
   PF2: capacity: 128 x 32 bit
   PF8K: capacity: 4096 x 16 bit */

typedef struct
{
    volatile uint32_t CTRL;           // 0x000 Packet FIFO Block Control
    volatile uint32_t SRAMCTRL0;      // 0x004 SRAM Test Control
    volatile uint32_t SRAMCTRL1;      // 0x008 SRAM Test Control
    volatile uint32_t STATUS;         // 0x00C FIFO Status
    volatile uint32_t PF0_PUSH_CTRL;  // 0x010 FIFO 0 Push Control
    volatile uint32_t PF0_POP_CTRL;   // 0x014 FIFO 0 Pop Control
    volatile uint32_t PF0_CNT;        // 0x018 FIFO 0 Count
    volatile uint32_t PF0_DATA;       // 0x01C FIFO 0 Push/Pop Data
    volatile uint32_t PF1_PUSH_CTRL;  // 0x020 FIFO 1 Push Control
    volatile uint32_t PF1_POP_CTRL;   // 0x024 FIFO 1 Pop Control
    volatile uint32_t PF1_CNT;        // 0x028 FIFO 1 Count
    volatile uint32_t PF1_DATA;       // 0x02C FIFO 1 Push/Pop Data
    volatile uint32_t PF2_PUSH_CTRL;  // 0x030 FIFO 2 Push Control
    volatile uint32_t PF2_POP_CTRL;   // 0x034 FIFO 2 Pop Control
    volatile uint32_t PF2_CNT;        // 0x038 FIFO 2 Count
    volatile uint32_t PF2_DATA;       // 0x03C FIFO 2 Push/Pop Data
    volatile uint32_t PF8K_PUSH_CTRL; // 0x040 FIFO 8K Push Control
    volatile uint32_t PF8K_POP_CTRL;  // 0x044 FIFO 8K Pop Control
    volatile uint32_t PF8K_CNT;       // 0x048 FIFO 8K Count
    volatile uint32_t PF8K_DATA;      // 0x04C FIFO 8K Push/Pop Data
    volatile uint32_t COLL_INTR;      // 0x050 FIFO Collision Interrupt
    volatile uint32_t COLL_INTR_EN;   // 0x054 FIFO Collision Interrupt Enable
} PKFB_typedef;

#define PKFB_CTRL_PF0_ENABLE 0x00000001
#define PKFB_CTRL_PF0_PUSH_MUX_FFE 0x00000002
#define PKFB_CTRL_PF0_POP_MUX_AP 0x00000004
#define PKFB_CTRL_PF0_PUSH_INT_MUX_AP 0x00000008
#define PKFB_CTRL_PF0_POP_INT_MUX_AP 0x00000010
#define PKFB_CTRL_PF0_FFE_SEL_FFE1 0x00000020

#define PKFB_CTRL_PF1_ENABLE 0x00000100
#define PKFB_CTRL_PF1_PUSH_MUX_FFE 0x00000200
#define PKFB_CTRL_PF1_POP_MUX_AP 0x00000400
#define PKFB_CTRL_PF1_PUSH_INT_MUX_AP 0x00000800
#define PKFB_CTRL_PF1_POP_INT_MUX_AP 0x00001000
#define PKFB_CTRL_PF1_FFE_SEL_FFE1 0x00002000

#define PKFB_CTRL_PF2_ENABLE 0x00010000
#define PKFB_CTRL_PF2_PUSH_MUX_FFE 0x00020000
#define PKFB_CTRL_PF2_POP_MUX_AP 0x00040000
#define PKFB_CTRL_PF2_PUSH_INT_MUX_AP 0x00080000
#define PKFB_CTRL_PF2_POP_INT_MUX_AP 0x00100000
#define PKFB_CTRL_PF2_FFE_SEL_FFE1 0x00200000

#define PKFB_CTRL_PF8K_ENABLE 0x01000000
#define PKFB_CTRL_PF8K_PUSH_MUX_FFE 0x02000000
#define PKFB_CTRL_PF8K_POP_MUX_AP 0x04000000
#define PKFB_CTRL_PF8K_PUSH_INT_MUX_AP 0x08000000
#define PKFB_CTRL_PF8K_POP_INT_MUX_AP 0x10000000
#define PKFB_CTRL_PF8K_FFE_SEL_FFE1 0x20000000

#define PKFB_PFx_CNT_EMPTY 0x8000

#endif