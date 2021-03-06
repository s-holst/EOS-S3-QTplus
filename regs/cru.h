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

#ifndef __CRU_H
#define __CRU_H

/* System Clock Summary

   External clock source of QTPLUS is a 32768 Hz crystal, called Real-Time Clock (RTC).
   Main system clock alternatives:
    1. On-chip High Speed Oscillator (HSO) driven by RTC up to 80 MHz (see: aip.h)
    2. Fast clock via Pad6, enabled by bootstrapping Pad8/Pad9 or registers.
*/

#include <stdint.h>

#define CRU ((CRU_typedef *)0x40004000)

typedef struct
{
    volatile uint32_t CLK_CTRL_A_0;           // 0x000 C10(M4-AHB/SRAM/VoiceSS,80MHz) [9] <1=divide> 0=passthrough [8:0]+2=divBy <4=divBy6>
    volatile uint32_t CLK_CTRL_A_1;           // 0x004
    volatile uint32_t CLK_CTRL_B_0;           // 0x008 C02(SPIm/eFUSE/FB/A1,40MHz) [9] <1=divide> 0=passthrough [8:0]+2=divBy <4=divBy6>
    volatile uint32_t reserved;               //
    volatile uint32_t CLK_CTRL_C_0;           // 0x010 C08X4(FFE,40MHz) [9] <1=divide> 0=passthrough [8:0]+2=divBy <4=divBy6>
    volatile uint32_t CLK_CTRL_D_0;           // 0x014 C11(UART/WDT/TIMER,10MHz) [9] <1=divide> 0=passthrough [8:0]+2=divBy <14=divBy16>
    volatile uint32_t CLK_CTRL_E_0;           // 0x018 C12
    volatile uint32_t reserved1;              //
    volatile uint32_t CLK_CTRL_F_0;           // 0x020 C16(FB:Sys_Clk0,72MHz) [9] <1=divide> 0=passthrough [8:0]+2=divBy <14=divBy16>
    volatile uint32_t CLK_CTRL_F_1;           // 0x024
    volatile uint32_t CLK_CTRL_G_0;           // 0x028 C18
    volatile uint32_t CLK_CTRL_H_0;           // 0x02C C19(ADC,typ1MHz) [9] <1=divide> 0=passthrough [8:0]+2=divBy <14=divBy16>
    volatile uint32_t reserved2;              //
    volatile uint32_t CLK_CTRL_I_0;           // 0x034 C21(FB:Sys_Clk1,72MHz) [9] <1=divide> 0=passthrough [8:0]+2=divBy <14=divBy16>
    volatile uint32_t CLK_CTRL_I_1;           // 0x038
    volatile uint32_t reverved3;              //
    volatile uint32_t C01_CLK_GATE;           // 0x040 C01(SPImConfig/eFUSE/I2S/AHB2APB/CfgDMA/FFE/FIFO/SDMA/A0,10MHz) Source:C10 [1] 1=SDMA SRAM [2] 1=PacketFIFO [3] 1=FFE [4] <1=AHB2APBbridge> [5] 1=I2S [6] 1=SDMA [7] <1=running> [9] <1=SPT>
    volatile uint32_t C02_CLK_GATE;           // 0x044
    volatile uint32_t C08_X4_CLK_GATE;        // 0x048 C08X4(FFE) gate.
    volatile uint32_t C08_X1_CLK_GATE;        // 0x04C C08X1(FFE) gate. [0] 1=FFE [2] 1=A0 [3] 1=AsyncFIFO0
    volatile uint32_t C10_FCLK_GATE;          // 0x050
    volatile uint32_t C11_CLK_GATE;           // 0x054 C11(UART/WDT/TIMER) gate. [0] <0=gated> 1=running. MISC->LOCK protected
    volatile uint32_t C12_CLK_GATE;           // 0x058
    volatile uint32_t CS_CLK_GATE;            // 0x05C
    volatile uint32_t CU_CLK_GATE;            // 0x060
    volatile uint32_t C16_CLK_GATE;           // 0x064 C16(FB:Sys_Clk0,72MHz) gate. [0] <0=gated> 1=running
    volatile uint32_t reversed4;              // 0x068
    volatile uint32_t C19_CLK_GATE;           // 0x06C
    volatile uint32_t C21_CLK_GATE;           // 0x070 C21(FB:Sys_Clk1,72MHz) gate. [0] <0=gated> 1=running
    volatile uint32_t reversed5[3];           //
    volatile uint32_t PF_SW_RESET;            // 0x080
    volatile uint32_t FFE_SW_RESET;           // 0x084
    volatile uint32_t FB_SW_RESET;            // 0x088 <1=reset> [0] C02 [2] C09 [4] C16/Sys_Clk0_Rst [5] C21/Sys_Clk1_Rst
    volatile uint32_t A1_SW_RESET;            // 0x08C
    volatile uint32_t AUDIO_MISC_SW_RST;      // 0x090
    volatile uint32_t FB_MISC_SW_RST_CTL;     // 0x094
    volatile uint32_t reversed6[26];          //
    volatile uint32_t CLK_CTRL_PMU;           // 0x100
    volatile uint32_t CRU_GENERAL;            // 0x104
    volatile uint32_t CRU_DEBUG;              // 0x108 [3:0] debug_mon[7/6] selection <0=none> 1=C00 2=C01 3=C02 4=C08X4 5=C08X1 6=C09 7=C10 8=C11 9=CS 10=C16 11=C19 12=C20/C32 13=C21 14=C23 15=C30/C31
    volatile uint32_t reversed7[1];           //
    volatile uint32_t C01_CLK_DIV;            // 0x110 C01(SPImConfig/eFUSE/I2S/AHB2APB/CfgDMA/FFE/FIFO/SDMA/A0,10MHz) Source:C10 [4] 0=gated <1=running> [3:0]+1=divBy <1=divBy2>
    volatile uint32_t C09_CLK_DIV;            // 0x114 C09((VoiceAPB/PIF/FB,10MHz) Source:C10 [4] 0=gated <1=running> [3:0]+1=divBy <1=divBy2>
    volatile uint32_t C31_CLK_DIV;            // 0x118
    volatile uint32_t C09_CLK_GATE;           // 0x11C C09 [0] <0=gated> 1=VoiceAPB [1] <0=gated> 1=PIF [2] <0=gated> 1=FB
    volatile uint32_t C30_31_CLK_GATE;        // 0x120
    volatile uint32_t CLK_DIVIDER_CLK_GATING; // 0x124
    volatile uint32_t reserved8[2];
    volatile uint32_t CLK_SWITCH_FOR_B;
    volatile uint32_t CLK_SWITCH_FOR_C;
    volatile uint32_t CLK_SWITCH_FOR_D;
    volatile uint32_t CLK_SWITCH_FOR_H;
    volatile uint32_t CLK_SWITCH_FOR_J;
    volatile uint32_t CLK_SWITCH_FOR_G;
} CRU_typedef;

// a divisor >= 2 enables the divider and sets its parameter to divisor-2.
#define CRU_CLK_CTRL_x_0_DIV_BY(x) ((x) < 2 ? 0x000 : (0x200 | ((x)-2)))

#define CRU_C01_CLK_GATE_PATH_1_SDMA_SRAM 0x02
#define CRU_C01_CLK_GATE_PATH_2_PF 0x04
#define CRU_C01_CLK_GATE_PATH_3_FFE 0x08
#define CRU_C01_CLK_GATE_PATH_4_AHB2APB 0x10
#define CRU_C01_CLK_GATE_PATH_5_I2S 0x20
#define CRU_C01_CLK_GATE_PATH_6_SDMA 0x40
#define CRU_C01_CLK_GATE_PATH_7 0x80
#define CRU_C01_CLK_GATE_PATH_9_SPT 0x200

#define CRU_C08_X4_CLK_GATE_PATH_0_Msk 0x01
#define CRU_C08_X1_CLK_GATE_PATH_0_Msk 0x01
#define CRU_C11_CLK_GATE_PATH_0_Msk 0x01

#define CRU_FB_SW_RESET_C02 0x01
#define CRU_FB_SW_RESET_C09 0x04
#define CRU_FB_SW_RESET_C16 0x10
#define CRU_FB_SW_RESET_C21 0x20
#define CRU_FB_SW_RESET_ALL 0x35

#endif