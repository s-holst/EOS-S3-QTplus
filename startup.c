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

   The code is based on startup_ARMCM4.c and vectors_CM4F_gcc.c under the
   following copyright:
    
   Copyright (c) 2011 - 2014 ARM LIMITED
   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

#include <stdint.h>

#include "regs/aip.h"
#include "regs/cru.h"

uint32_t uptime_ms = 0; // global: uptime in milliseconds, always counting up, wraps in about 49 days.

extern uint32_t __etext;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern void _start(void) __attribute__((noreturn)); // C library entry point

void SysTick_Handler()
{
    uptime_ms++;
}

void Reset_Handler(void)
{
    uint32_t *pSrc, *pDest;

    pSrc = &__etext;
    pDest = &__data_start__;
    while (pDest < &__data_end__)
        *pDest++ = *pSrc++;

    // Set main clock to 72 MHz:
    AIP->OSC_CTRL_1 = 2194;
    CRU->CLK_CTRL_A_0 = 0; // C10=72MHz

    // Set up SysTick:
    *((uint32_t *)0xE000E014) = 72000; // reload value
    *((uint32_t *)0xE000E018) = 0;
    *((uint32_t *)0xE000E010) = 7; // use processor clock, enable interrupt, enable timer.

    _start();
}

void Default_Handler(void)
{
    while (1)
        ;
}

__attribute__((weak, alias("Default_Handler"))) extern void NMI_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void HardFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void MemManage_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void BusFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void UsageFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void SVC_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void DebugMon_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void PendSV_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void SwInt2_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void SwInt1_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Ffe0Msg_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void FbMsg_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void SensorGpio_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void M4SramSleep_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Uart_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Timer_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void CpuWdtInt_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void CpuWdtRst_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void BusTimeout_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Fpu_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Pkfb_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void I2s_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Audio_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void SpiMs_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void CfgDma_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void PmuTimer_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void AdcDone_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void RtcAlarm_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void ResetInt_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Ffe0_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void FfeWdt_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void ApBoot_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void LDO30_PG_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void LDO50_PG_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void SRAM_128KB_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void LPSD_Voice_Det_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void DMIC_Voice_Det_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Sdma1Done_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Sdma2Done_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Sdma3Done_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Sdma4Done_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Sdma5Done_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Sdma6Done_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Sdma7Done_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Sdma8Done_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Sdma9Done_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Sdma10Done_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Sdma11Done_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void ApPDMClkOn_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void ApPDMClkOff_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Dmac0BlkDone_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Dmac0BufDone_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Dmac1BlkDone_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Dmac1BufDone_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void Sdma0Done_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void SdmaErr_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void I2S_SlvM4TxOr_Handler(void);
__attribute__((weak, alias("Default_Handler"))) extern void lpsdVoiceOffHandler(void);
__attribute__((weak, alias("Default_Handler"))) extern void dmicVoiceOffHandler(void);

/* Exception and Interrupt Vector Table */

extern uint32_t __StackTop;

typedef void (*intfunc)(void);

typedef union
{
    void (*int_func)(void);
    void *__ptr;
    int __val;
} intvec_elem;

const intvec_elem __Vectors[] __attribute__((section(".isr_vector"))) = {
    (intfunc)&__StackTop,   // 0x000 Main Stack Pointer
    Reset_Handler,          // 0x004 Reset
    NMI_Handler,            // 0x008 NMI
    HardFault_Handler,      // 0x00C Hard Fault
    MemManage_Handler,      // 0x010 Mem Manage Fault
    BusFault_Handler,       // 0x014 Bus Fault
    UsageFault_Handler,     // 0x018 Usage Fault
    0,                      // 0x01C
    0,                      // 0x020
    0,                      // 0x024
    0,                      // 0x028
    SVC_Handler,            // 0x02C SVC
    DebugMon_Handler,       // 0x030 Debug Monitor
    0,                      // 0x034
    PendSV_Handler,         // 0x038 Pend SV
    SysTick_Handler,        // 0x03C SysTick
    SwInt2_Handler,         // 0x040 Software Interrupt 2
    SwInt1_Handler,         // 0x044 Software Interrupt 1
    0,                      // 0x048
    Ffe0Msg_Handler,        // 0x04C FFE0 Message
    FbMsg_Handler,          // 0x050 Fabric Message
    SensorGpio_Handler,     // 0x054 Sensor/GPIO
    M4SramSleep_Handler,    // 0x058 M4 SRAM Sleep
    Uart_Handler,           // 0x05C UART
    Timer_Handler,          // 0x060 TIMER
    CpuWdtInt_Handler,      // 0x064 CPU WDOG_INTR
    CpuWdtRst_Handler,      // 0x068 CPU WDOG_RST
    BusTimeout_Handler,     // 0x06C Bus Timeout
    Fpu_Handler,            // 0x070 FPU
    Pkfb_Handler,           // 0x074 PKFB
    I2s_Handler,            // 0x078
    Audio_Handler,          // 0x07C
    SpiMs_Handler,          // 0x080 SPI_MS
    CfgDma_Handler,         // 0x084 CFG_DMA
    PmuTimer_Handler,       // 0x088 PMU Timer
    AdcDone_Handler,        // 0x08C ADC Done
    RtcAlarm_Handler,       // 0x090 RTC Alarm
    ResetInt_Handler,       // 0x094 Reset Interrupt
    Ffe0_Handler,           // 0x098 FFE0 Combined
    FfeWdt_Handler,         // 0x09C
    ApBoot_Handler,         // 0x0A0 AP Boot
    LDO30_PG_Handler,       // 0x0A4 LDO30 PG INTR
    LDO50_PG_Handler,       // 0x0A8 LDO50 PG INTR
    SRAM_128KB_Handler,     // 0x0AC
    LPSD_Voice_Det_Handler, // 0x0B0 LPSD Voice Det
    DMIC_Voice_Det_Handler, // 0x0B4 DMIC Voice Det
    0,                      // 0x0B8
    Sdma1Done_Handler,      // 0x0BC SDMA_DONE
    Sdma2Done_Handler,      // 0x0C0 SDMA_DONE
    Sdma3Done_Handler,      // 0x0C4 SDMA_DONE
    Sdma4Done_Handler,      // 0x0C8 SDMA_DONE
    Sdma5Done_Handler,      // 0x0CC SDMA_DONE
    Sdma6Done_Handler,      // 0x0D0 SDMA_DONE
    Sdma7Done_Handler,      // 0x0D4 SDMA_DONE
    Sdma8Done_Handler,      // 0x0D8 SDMA_DONE
    Sdma9Done_Handler,      // 0x0DC SDMA_DONE
    Sdma10Done_Handler,     // 0x0E0 SDMA_DONE
    Sdma11Done_Handler,     // 0x0E4 SDMA_DONE
    ApPDMClkOn_Handler,     // 0x0E8 AP_PDM_CLK_ON
    ApPDMClkOff_Handler,    // 0x0EC AP_PDM_CLK_OFF
    Dmac0BlkDone_Handler,   // 0x0F0 DMAC0_BLK_DONE
    Dmac0BufDone_Handler,   // 0x0F4 DMAC0_BUF_DONE
    Dmac1BlkDone_Handler,   // 0x0F8 DMAC1_BLK_DONE
    Dmac1BufDone_Handler,   // 0x0FC DMAC1_BUF_DONE
    Sdma0Done_Handler,      // 0x100 SDMA_DONE[0]
    SdmaErr_Handler,        // 0x104 SDMA_ERR
    I2S_SlvM4TxOr_Handler,  // 0x108 I2SSLV_M4_tx_or_intr
    lpsdVoiceOffHandler,    // 0x10C LPSD_VOICE_OFF
    dmicVoiceOffHandler,    // 0x110 DMIC_VOICE_OFF
    0,                      // 0x114
    0,                      // 0x118
    0,                      // 0x11C
    /* 0x120 Configuration Manager boot header.
       32-bit word stored in little-endian format!
       0x20 is a fixed EOS S3 id checked by bootloader (stored at 0x123).
       0x02 is a baudrate multiplier (SPI->BAUDR is set to 2* this value) (stored at 0x122).
       0x1FFF is the number of 8-byte words in the image (here: 64kiBytes) (stored at 0x120). */
    {.__val = (0x20021FFF)}};