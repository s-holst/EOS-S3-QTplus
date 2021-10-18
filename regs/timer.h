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

#ifndef __REGS_TIMER_H
#define __REGS_TIMER_H

#include <stdint.h>

#define TIMER ((TIMER_typedef *)0x40013000)

typedef struct
{
    volatile uint32_t CTRL;               // 0x00 [0] 1=enable [1] 1=enable by ext. input [2] 1=clock by ext. input [3] 1=int. enable
    volatile uint32_t VALUE;              // 0x04 current value
    volatile uint32_t RELOAD;             // 0x08 reload value (write sets current value as well)
    volatile uint32_t INTSTATUS_INTCLEAR; // 0x0c [0]W1C interrupt, write 1 to clear
    volatile uint32_t reserved[1008];     //
    volatile uint32_t PID4;               // 0xfd0
    volatile uint32_t PID5;               // 0xfd4
    volatile uint32_t PID6;               // 0xfd8
    volatile uint32_t PID7;               // 0xfdc
    volatile uint32_t PID0;               // 0xfe0
    volatile uint32_t PID1;               // 0xfe4
    volatile uint32_t PID2;               // 0xfe8
    volatile uint32_t PID3;               // 0xfec
    volatile uint32_t CID0;               // 0xff0
    volatile uint32_t CID1;               // 0xff4
    volatile uint32_t CID2;               // 0xff8
    volatile uint32_t CID3;               // 0xffc
} TIMER_typedef;

#endif