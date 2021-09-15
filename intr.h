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

#ifndef __INTR_H
#define __INTR_H

#include <stdint.h>

typedef struct
{
    volatile uint32_t GPIO_INTR;                /* Address offset: 0x00 */
    volatile uint32_t GPIO_INTR_RAW;            /* Address offset: 0x04 */
    volatile uint32_t GPIO_INTR_TYPE;           /* Address offset: 0x08 */
    volatile uint32_t GPIO_INTR_POL;            /* Address offset: 0x0C */
    volatile uint32_t GPIO_INTR_EN_AP;          /* Address offset: 0x10 */
    volatile uint32_t GPIO_INTR_EN_M4;          /* Address offset: 0x14 */
    volatile uint32_t GPIO_INTR_EN_FFE0;        /* Address offset: 0x18 */
    volatile uint32_t GPIO_INTR_EN_FFE1;        /* Address offset: 0x1C */
    volatile uint32_t reserved1[4];
    volatile uint32_t OTHER_INTR;               /* Address offset: 0x30 */
    volatile uint32_t OTHER_INTR_EN_AP;         /* Address offset: 0x34 */
    volatile uint32_t OTHER_INTR_EN_M4;         /* Address offset: 0x38 */
    volatile uint32_t reserved2[1];
    volatile uint32_t SOFTWARE_INTR_1;          /* Address offset: 0x40 */
    volatile uint32_t SOFTWARE_INTR_1_EN_AP;    /* Address offset: 0x44 */
    volatile uint32_t SOFTWARE_INTR_1_EN_M4;    /* Address offset: 0x48 */
    volatile uint32_t reserved3[1];
    volatile uint32_t SOFTWARE_INTR_2;          /* Address offset: 0x50 */
    volatile uint32_t SOFTWARE_INTR_2_EN_AP;    /* Address offset: 0x54 */
    volatile uint32_t SOFTWARE_INTR_2_EN_M4;    /* Address offset: 0x58 */
    volatile uint32_t reserved4[1];
    volatile uint32_t FFE_INTR;                 /* Address offset: 0x60 */
    volatile uint32_t FFE_INTR_EN_AP;           /* Address offset: 0x64 */
    volatile uint32_t FFE_INTR_EN_M4;           /* Address offset: 0x68 */
    volatile uint32_t reserved5[1];
    volatile uint32_t FFE1_FB_INTR;             /* Address offset: 0x70 */
    volatile uint32_t FFE1_FB_INTR_EN_AP;       /* Address offset: 0x74 */
    volatile uint32_t FFE1_FB_INTR_EN_M4;       /* Address offset: 0x78 */
    volatile uint32_t reserved6[1];
    volatile uint32_t FB_INTR;                  /* Address offset: 0x80 */
    volatile uint32_t FB_INTR_RAW;              /* Address offset: 0x84 */
    volatile uint32_t FB_INTR_TYPE;             /* Address offset: 0x88 */
    volatile uint32_t FB_INTR_POL;              /* Address offset: 0x8C */
    volatile uint32_t FB_INTR_EN_AP;            /* Address offset: 0x90 */
    volatile uint32_t FB_INTR_EN_M4;            /* Address offset: 0x94 */
    volatile uint32_t reserved7[2];
    volatile uint32_t M4_MEM_AON_INTR;	/* Address offset: 0xA0 */
    volatile uint32_t M4_MEM_AON_INTR_EN;	/* Address offset: 0xA4 */
} INTR_typedef;

#define INTR_BASE (0x40004800)
#define INTR ((INTR_typedef*) INTR_BASE)

#define UART_INTR_EN_M4         ((uint32_t) (0x00000002))

#endif