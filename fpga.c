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

#include "regs/iomux.h"
#include "regs/cru.h"
#include "regs/pmu.h"
#include "regs/fpga.h"

void fpga_sleep(uint32_t uiCycles)
{
    for (int i = 0; i < uiCycles; i++)
        PMU->GEN_PURPOSE_1 = i << 4;
}

void fpga_configure(uint32_t *puiBitstream)
{
    IOMUX->PAD[19] = IOMUX_PAD_E_4MA | IOMUX_PAD_P_PULLDOWN; // Pull pad19 low for FPGA programming.

    // ensure FPGA power up
    PMU->FFE_FB_PF_SW_WU |= PMU_FFE_FB_PF_SW_WU_FB_WU_Msk;
    while (!(PMU->FB_STATUS & 1))
        ;

    // C02 already active for SPIm

    CRU->C09_CLK_DIV = 0x017;                        // C09=9MHz (divBy8) for PIF (Programming Interface)
    CRU->C09_CLK_GATE |= 0x6;                        // enable clock for PIF and FB
    CRU->C08_X1_CLK_GATE |= 0x4;                     // C08X1 to A0
    CRU->CLK_CTRL_F_0 = CRU_CLK_CTRL_x_0_DIV_BY(6);  // C16=Sys_Clk0=12MHz
    CRU->CLK_CTRL_I_0 = CRU_CLK_CTRL_x_0_DIV_BY(72); // C21=Sys_Clk1=1MHz
    CRU->C16_CLK_GATE = 1;
    CRU->C21_CLK_GATE = 1;
    CRU->FB_SW_RESET |= CRU_FB_SW_RESET_ALL;

    PMU->FB_ISOLATION = 1;                                 // ensure isolation
    PMU->GEN_PURPOSE_0 |= PMU_GEN_PURPOSE_0_FB_CFG_ENABLE; // ensure cfg mode
    PIF->CTRL = 0x0000bdff;                                // enable PIF

    fpga_sleep(50); // wait some time for FPGA reset

    for (int i = 0; i < (75960 / 4); i++)
        PIF->DATA = puiBitstream[i];

    fpga_sleep(50); // wait some time for FPGA reset

    PIF->CTRL = 0x0;

    PMU->GEN_PURPOSE_1 = 0x90; // not sure what this is doing...

    PMU->GEN_PURPOSE_0 = 0; // disable config mode

    fpga_sleep(500); // wait some time before releasing LTH_ENB

    PMU->FB_ISOLATION = 0; // release from isolation

    fpga_sleep(50); // wait some time for FPGA reset

    CRU->FB_SW_RESET = 0;
    CRU->FB_MISC_SW_RST_CTL = 0;

    // Disable driver of pad 19.
    IOMUX->PAD[19] = IOMUX_PAD_E_4MA | IOMUX_PAD_P_PULLDOWN | IOMUX_PAD_OEN_DISABLE | IOMUX_PAD_REN_ENABLE;
}
