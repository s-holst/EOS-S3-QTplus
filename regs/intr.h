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

#ifndef __INTR_H
#define __INTR_H

#include <stdint.h>

#define INTR ((INTR_typedef *)0x40004800)

typedef struct
{
    volatile uint32_t GPIO_INTR;             // 0x00 [7:0]RW1C 1=GPIOx interrupt triggered
    volatile uint32_t GPIO_INTR_RAW;         // 0x04 [7:0]R raw logic value of GPIOx
    volatile uint32_t GPIO_INTR_TYPE;        // 0x08 [7:0] trigger type <0=level> 1=edge
    volatile uint32_t GPIO_INTR_POL;         // 0x0C [7:0] trigger polarity <0=low/fall> 1=high/rise
    volatile uint32_t GPIO_INTR_EN_AP;       // 0x10
    volatile uint32_t GPIO_INTR_EN_M4;       // 0x14 [7:0] enable for M4 <0=disable> 1=enable
    volatile uint32_t GPIO_INTR_EN_FFE0;     // 0x18
    volatile uint32_t GPIO_INTR_EN_FFE1;     // 0x1C
    volatile uint32_t reserved1[4];          //
    volatile uint32_t OTHER_INTR;            // 0x30
    volatile uint32_t OTHER_INTR_EN_AP;      // 0x34
    volatile uint32_t OTHER_INTR_EN_M4;      // 0x38
    volatile uint32_t reserved2[1];          //
    volatile uint32_t SOFTWARE_INTR_1;       // 0x40
    volatile uint32_t SOFTWARE_INTR_1_EN_AP; // 0x44
    volatile uint32_t SOFTWARE_INTR_1_EN_M4; // 0x48
    volatile uint32_t reserved3[1];          //
    volatile uint32_t SOFTWARE_INTR_2;       // 0x50
    volatile uint32_t SOFTWARE_INTR_2_EN_AP; // 0x54
    volatile uint32_t SOFTWARE_INTR_2_EN_M4; // 0x58
    volatile uint32_t reserved4[1];          //
    volatile uint32_t FFE_INTR;              // 0x60
    volatile uint32_t FFE_INTR_EN_AP;        // 0x64
    volatile uint32_t FFE_INTR_EN_M4;        // 0x68
    volatile uint32_t reserved5[1];          //
    volatile uint32_t FFE1_FB_INTR;          // 0x70
    volatile uint32_t FFE1_FB_INTR_EN_AP;    // 0x74
    volatile uint32_t FFE1_FB_INTR_EN_M4;    // 0x78
    volatile uint32_t reserved6[1];          //
    volatile uint32_t FB_INTR;               // 0x80
    volatile uint32_t FB_INTR_RAW;           // 0x84
    volatile uint32_t FB_INTR_TYPE;          // 0x88
    volatile uint32_t FB_INTR_POL;           // 0x8C
    volatile uint32_t FB_INTR_EN_AP;         // 0x90
    volatile uint32_t FB_INTR_EN_M4;         // 0x94
    volatile uint32_t reserved7[2];          //
    volatile uint32_t M4_MEM_AON_INTR;       // 0xA0
    volatile uint32_t M4_MEM_AON_INTR_EN;    // 0xA4
} INTR_typedef;

#define INTR_OTHER_INTR_EN_M4_UART 0x00000002

// TODO: use CMSIS?

#define NVIC ((NVIC_typedef *)0xE000E100)

typedef struct
{
    volatile uint32_t ISER[8];        // 0x000 (R/W)  Interrupt Set Enable Register
    volatile uint32_t RESERVED0[24];  //
    volatile uint32_t ICER[8];        // 0x080 (R/W)  Interrupt Clear Enable Register
    volatile uint32_t RSERVED1[24];   //
    volatile uint32_t ISPR[8];        // 0x100 (R/W)  Interrupt Set Pending Register
    volatile uint32_t RESERVED2[24];  //
    volatile uint32_t ICPR[8];        // 0x180 (R/W)  Interrupt Clear Pending Register
    volatile uint32_t RESERVED3[24];  //
    volatile uint32_t IABR[8];        // 0x200 (R/W)  Interrupt Active bit Register
    volatile uint32_t RESERVED4[56];  //
    volatile uint8_t IP[240];         // 0x300 (R/W)  Interrupt Priority Register (8Bit wide)
    volatile uint32_t RESERVED5[644]; //
    volatile uint32_t STIR;           // 0xE00 ( /W)  Software Trigger Interrupt Register
} NVIC_typedef;

#endif