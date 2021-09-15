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

#ifndef __CRU_H
#define __CRU_H

/*

System Clock Summary

External clock source of QTPLUS is a 32768 Hz crystal, called Real-Time Clock (RTC).
Main system clock alternatives:
  1. On-chip High Speed Oscillator (HSO) driven by RTC. Range: 2.195 MHz ... 80 MHz, default: 76.97 MHz
  2. Fast clock via GPIO6, enabled by bootstrapping GPIO8/GPIO9 or registers.

HSO frequency is controlled via AIP registers (aip.h).

EOS S3 contains 19 clock domains.


*/

#include <stdint.h>

typedef struct
{
    volatile uint32_t CLK_CTRL_A_0;            // 0x000 C10
    volatile uint32_t CLK_CTRL_A_1;            // 0x004 
    volatile uint32_t CLK_CTRL_B_0;            // 0x008 C02
    volatile uint32_t reserved;
    volatile uint32_t CLK_CTRL_C_0;            // 0x010 C08X4(FFE,40MHz) divider: [9] en; div by ([8:0]+2) 0..6..510
    volatile uint32_t CLK_CTRL_D_0;            // 0x014 C11(UART/WDT/TIMER,10MHz) divider: [9] en; div by ([8:0]+2) 0..6..510
    volatile uint32_t CLK_CTRL_E_0;            // 0x018 C12
    volatile uint32_t reserved1;
    volatile uint32_t CLK_CTRL_F_0;            // 0x020 C16
    volatile uint32_t CLK_CTRL_F_1;            // 0x024
    volatile uint32_t CLK_CTRL_G_0;            // 0x028 C18
    volatile uint32_t CLK_CTRL_H_0;            // 0x02C C19
    volatile uint32_t reserved2;
    volatile uint32_t CLK_CTRL_I_0;            // 0x034 C21
    volatile uint32_t CLK_CTRL_I_1;            // 0x038
    volatile uint32_t reverved3;
    volatile uint32_t C01_CLK_GATE;            // 0x040
    volatile uint32_t C02_CLK_GATE;            // 0x044 
    volatile uint32_t C08_X4_CLK_GATE;		     // 0x048 gate for C08X4 (FFE)
    volatile uint32_t C08_X1_CLK_GATE;		     // 0x04C gate for C08X1 (FFE)
    volatile uint32_t C10_FCLK_GATE;		       // 0x050
    volatile uint32_t C11_CLK_GATE;			       // 0x054 C11(UART/WDT/TIMER) gate. MISC->LOCK protected
    volatile uint32_t C12_CLK_GATE;            // 0x058
    volatile uint32_t CS_CLK_GATE;             // 0x05C
    volatile uint32_t CU_CLK_GATE;             // 0x060
    volatile uint32_t C16_CLK_GATE;            // 0x064
    volatile uint32_t reversed4;               // 0x068
    volatile uint32_t C19_CLK_GATE;            // 0x06C
    volatile uint32_t C21_CLK_GATE;            // 0x070
    volatile uint32_t reversed5[3];
    volatile uint32_t PF_SW_RESET;             // 0x080
    volatile uint32_t FFE_SW_RESET;            // 0x084
    volatile uint32_t FB_SW_RESET;             // 0x088
    volatile uint32_t A1_SW_RESET;             // 0x08C
    volatile uint32_t AUDIO_MISC_SW_RST;       // 0x090
    volatile uint32_t FB_MISC_SW_RST_CTL;      // 0x094
    volatile uint32_t reversed6[26];
    volatile uint32_t CLK_CTRL_PMU;            // 0x100
    volatile uint32_t CRU_GENERAL;             // 0x104
    volatile uint32_t CRU_DEBUG;               // 0x108
    volatile uint32_t reversed7[1];
    volatile uint32_t C01_CLK_DIV;             // 0x110
    volatile uint32_t C09_CLK_DIV;             // 0x114
    volatile uint32_t C31_CLK_DIV;             // 0x118
    volatile uint32_t C09_CLK_GATE;            // 0x11C
    volatile uint32_t C30_31_CLK_GATE;         // 0x120
    volatile uint32_t CLK_DIVIDER_CLK_GATING;  // 0x124
    volatile uint32_t reserved8[2];
    volatile uint32_t CLK_SWITCH_FOR_B;
    volatile uint32_t CLK_SWITCH_FOR_C;
    volatile uint32_t CLK_SWITCH_FOR_D;
    volatile uint32_t CLK_SWITCH_FOR_H;
    volatile uint32_t CLK_SWITCH_FOR_J;
    volatile uint32_t CLK_SWITCH_FOR_G;
} CRU_typedef;

#define CRU_BASE (0x40004000)
#define CRU ((CRU_typedef*) CRU_BASE)

#define CRU_CLK_CTRL_x_0_DIV_BY_1 ((uint32_t) (0x00000000))
#define CRU_CLK_CTRL_x_0_DIV_BY_2 ((uint32_t) (0x00000200))
#define CRU_CLK_CTRL_x_0_DIV_BY_3 ((uint32_t) (0x00000201))
#define CRU_CLK_CTRL_x_0_DIV_BY_4 ((uint32_t) (0x00000202))
#define CRU_CLK_CTRL_x_0_DIV_BY_5 ((uint32_t) (0x00000203))
#define CRU_CLK_CTRL_x_0_DIV_BY_6 ((uint32_t) (0x00000204))
#define CRU_CLK_CTRL_x_0_DIV_BY_7 ((uint32_t) (0x00000205))
#define CRU_CLK_CTRL_x_0_DIV_BY_8 ((uint32_t) (0x00000206))
#define CRU_CLK_CTRL_x_0_DIV_BY_9 ((uint32_t) (0x00000207))
#define CRU_CLK_CTRL_x_0_DIV_BY_10 ((uint32_t) (0x00000208))
#define CRU_CLK_CTRL_x_0_DIV_BY_11 ((uint32_t) (0x00000209))
#define CRU_CLK_CTRL_x_0_DIV_BY_12 ((uint32_t) (0x0000020a))
#define CRU_CLK_CTRL_x_0_DIV_BY_13 ((uint32_t) (0x0000020b))
#define CRU_CLK_CTRL_x_0_DIV_BY_14 ((uint32_t) (0x0000020c))
#define CRU_CLK_CTRL_x_0_DIV_BY_15 ((uint32_t) (0x0000020d))
#define CRU_CLK_CTRL_x_0_DIV_BY_16 ((uint32_t) (0x0000020e))
#define CRU_CLK_CTRL_x_0_DIV_BY_17 ((uint32_t) (0x0000020f))

#define CRU_C01_CLK_GATE_PATH_3_Msk ((uint32_t) (0x00000008))

#define CRU_C08_X4_CLK_GATE_PATH_0_Msk ((uint32_t) (0x00000001))
#define CRU_C08_X1_CLK_GATE_PATH_0_Msk ((uint32_t) (0x00000001))
#define CRU_C11_CLK_GATE_PATH_0_Msk    ((uint32_t) (0x00000001))

#endif