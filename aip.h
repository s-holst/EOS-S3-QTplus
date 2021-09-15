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

#ifndef __AIP_H
#define __AIP_H

#include <stdint.h>

/*
    Analog IP - Clock Source and Oscillator Control
*/
typedef struct
{
	volatile uint32_t reserved;			/* Address offset: 0x00 */
	volatile uint32_t RTC_CTRL_1;		/* Address offset: 0x04 */
	volatile uint32_t RTC_CTRL_2;		/* Address offset: 0x08 */
	volatile uint32_t RTC_CTRL_3;		/* Address offset: 0x0C */
	volatile uint32_t RTC_CTRL_4;		/* Address offset: 0x10 */
	volatile uint32_t RTC_CTRL_5;		/* Address offset: 0x14 */
	volatile uint32_t RTC_CTRL_6;		/* Address offset: 0x18 */
	volatile uint32_t RTC_CTRL_7;		/* Address offset: 0x1C */
	volatile uint32_t RTC_STA_0;		/* Address offset: 0x20 */
	volatile uint32_t RTC_STA_1;		/* Address offset: 0x24 */
	volatile uint32_t reserved1[22];
	volatile uint32_t OSC_CTRL_0;		// 0x080 
	volatile uint32_t OSC_CTRL_1;		// 0x084 HSO freq = 32768*([12:0]+3), [5:0] must be 0, 64(2.2MHz)..2349(77.1MHz)..2432(79.8MHz)
	volatile uint32_t OSC_CTRL_2;		/* Address offset: 0x88 */
	volatile uint32_t OSC_CTRL_3;		/* Address offset: 0x8C */
	volatile uint32_t OSC_CTRL_4;		/* Address offset: 0x90 */
	volatile uint32_t OSC_CTRL_5;		/* Address offset: 0x94 */
	volatile uint32_t OSC_CTRL_6;		/* Address offset: 0x98 */
	volatile uint32_t OSC_CTRL_7;		/* Address offset: 0x9C */
	volatile uint32_t OSC_STA_0;		/* Address offset: 0xA0 */
	volatile uint32_t OSC_STA_1;		/* Address offset: 0xA4 */
	volatile uint32_t reserved2[22];
	volatile uint32_t APC_CTRL_0;		/* Address offset: 0x100 */
	volatile uint32_t APC_CTRL_1;		/* Address offset: 0x104 */
	volatile uint32_t APC_CTRL_2;		/* Address offset: 0x108 */
	volatile uint32_t APC_CTRL_3;		/* Address offset: 0x10C */
	volatile uint32_t APC_CTRL_4;		/* Address offset: 0x110 */
	volatile uint32_t APC_CTRL_5;		/* Address offset: 0x114 */
	volatile uint32_t APC_CTRL_6;		/* Address offset: 0x118 */
	volatile uint32_t APC_CTRL_7;		/* Address offset: 0x11C */
	volatile uint32_t APC_STA_0;		/* Address offset: 0x120 */
	volatile uint32_t APC_STA_1;		/* Address offset: 0x124 */
	volatile uint32_t reserved3[22];
	volatile uint32_t RING_OSC;			/* Address offset: 0x180 */
	volatile uint32_t reserved4[31];
	volatile uint32_t LD0_30_CTRL_0;
	volatile uint32_t LD0_30_CTRL_1;
	volatile uint32_t reserved5[2];
	volatile uint32_t LD0_50_CTRL_0;
	volatile uint32_t LD0_50_CTRL_1;
} AIP_typedef;

#define AIP_BASE (0x40005400)
#define AIP ((AIP_typedef*) AIP_BASE)

#endif