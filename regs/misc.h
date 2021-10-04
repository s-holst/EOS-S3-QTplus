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

#ifndef __MISC_H
#define __MISC_H

#include <stdint.h>

#define MISC ((MISC_typedef *)0x40005000)

typedef struct
{
    volatile uint32_t DBG_MON;            // 0x000
    volatile uint32_t SUBSYS_DBG_MON_SEL; // 0x004
    volatile uint32_t A0_DBG_MON_SEL;     // 0x008
    volatile uint32_t A0_PMU_DBG_MON_SEL; // 0x00C
    volatile uint32_t reserved010[60];    // 0x010
    volatile uint32_t IO_INPUT;           // 0x100 [7:0]R input of GPIO7..GPIO0
    volatile uint32_t IO_OUTPUT;          // 0x104 [7:0]W output for GPIO7..GPIO0
    volatile uint32_t reserved108[2];     // 0x108
    volatile uint32_t SW_MB_1;            // 0x110
    volatile uint32_t SW_MB_2;            // 0x114
    volatile uint32_t reserved118[58];    // 0x118
    volatile uint32_t PAD_SEL18;          // 0x200
    volatile uint32_t reserved204[3];     // 0x204
    volatile uint32_t CONFIG_MEM128_AON;  // 0x210
    volatile uint32_t reserved214[63];    // 0x214
    volatile uint32_t LOCK_KEY_CTRL;      // 0x310
    volatile uint32_t reserved314[58];    // 0x314
    volatile uint32_t FB_DEVICE_ID;       // 0x3FC [15:0]R Fabric Device ID set by hw design (qlal4s3b_cell_macro.Device_ID)
} MISC_typedef;

#define MISC_LOCK_KEY_CTRL_UNLOCK 0x1ACCE551

#endif