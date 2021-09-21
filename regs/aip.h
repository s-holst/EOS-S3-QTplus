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

#ifndef __AIP_H
#define __AIP_H

#include <stdint.h>

/* Analog IP - Clock Source and Oscillator Control */
#define AIP ((AIP_typedef *)0x40005400)

typedef struct
{
    volatile uint32_t reserved000;     //
    volatile uint32_t RTC_CTRL_1;      // 0x004
    volatile uint32_t RTC_CTRL_2;      // 0x008
    volatile uint32_t RTC_CTRL_3;      // 0x00C
    volatile uint32_t RTC_CTRL_4;      // 0x010
    volatile uint32_t RTC_CTRL_5;      // 0x014
    volatile uint32_t RTC_CTRL_6;      // 0x018
    volatile uint32_t RTC_CTRL_7;      // 0x01C
    volatile uint32_t RTC_STA_0;       // 0x020
    volatile uint32_t RTC_STA_1;       // 0x024
    volatile uint32_t reserved028[22]; //
    volatile uint32_t OSC_CTRL_0;      // 0x080
    volatile uint32_t OSC_CTRL_1;      // 0x084 HSO freq=32768*([12:0]+3), [5:0] must be 0, <2349(77.1MHz)>, 64(2.2MHz)..2432(79.8MHz)
    volatile uint32_t OSC_CTRL_2;      // 0x088
    volatile uint32_t OSC_CTRL_3;      // 0x08C
    volatile uint32_t OSC_CTRL_4;      // 0x090
    volatile uint32_t OSC_CTRL_5;      // 0x094
    volatile uint32_t OSC_CTRL_6;      // 0x098
    volatile uint32_t OSC_CTRL_7;      // 0x09C
    volatile uint32_t OSC_STA_0;       // 0x0A0
    volatile uint32_t OSC_STA_1;       // 0x0A4
    volatile uint32_t reserved0A8[22]; //
    volatile uint32_t APC_CTRL_0;      // 0x100
    volatile uint32_t APC_CTRL_1;      // 0x104
    volatile uint32_t APC_CTRL_2;      // 0x108
    volatile uint32_t APC_CTRL_3;      // 0x10C
    volatile uint32_t APC_CTRL_4;      // 0x110
    volatile uint32_t APC_CTRL_5;      // 0x114
    volatile uint32_t APC_CTRL_6;      // 0x118
    volatile uint32_t APC_CTRL_7;      // 0x11C
    volatile uint32_t APC_STA_0;       // 0x120
    volatile uint32_t APC_STA_1;       // 0x124
    volatile uint32_t reserved128[22]; //
    volatile uint32_t RING_OSC;        // 0x180
    volatile uint32_t reserved184[31];
    volatile uint32_t LD0_30_CTRL_0;
    volatile uint32_t LD0_30_CTRL_1;
    volatile uint32_t reserved5[2];
    volatile uint32_t LD0_50_CTRL_0;
    volatile uint32_t LD0_50_CTRL_1;
} AIP_typedef;

#endif