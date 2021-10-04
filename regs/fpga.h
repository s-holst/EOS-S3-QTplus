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

#ifndef __REGS_FPGA_H
#define __REGS_FPGA_H

#include <stdint.h>

/* Programming Interface (PIF) aka. Configuration Control (CFG_CTL) for loading bitstreams. */
#define PIF ((PIF_typedef *)0x40014000)

typedef struct
{
    volatile uint32_t CTRL;                // 0x0000
    volatile uint32_t MAX_BL_CNT;          // 0x0004
    volatile uint32_t MAX_WL_CNT;          // 0x0008
    volatile uint32_t reserved000C[0x3fc]; //
    volatile uint32_t DATA;                // 0x0FFC
    volatile uint32_t reserved1000[0xc00]; //
    volatile uint32_t RAMFIFO0[0x400];     // 0x8000
    volatile uint32_t RAMFIFO1[0x400];     // 0x9000
    volatile uint32_t RAMFIFO2[0x400];     // 0xA000
    volatile uint32_t RAMFIFO3[0x400];     // 0xB000
} PIF_typedef;

#define FPGA_WB_BASE 0x40020000

#endif