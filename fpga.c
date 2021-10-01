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

#define CFG_CTL_CFG_DATA (*(volatile uint32_t *)(0x40014FFC))
#define CFG_CTL_CFG_CTL (*(volatile uint32_t *)(0x40014000))

void fpga_configure(uint32_t *puiBitstream)
{
    IOMUX->PAD[19] = IOMUX_PAD_E_4MA | IOMUX_PAD_P_PULLDOWN; // Pull pad19 low for FPGA programming.

    // ensure FPGA power up
    PMU->FFE_FB_PF_SW_WU |= PMU_FFE_FB_PF_SW_WU_FB_WU_Msk;
    while (!(PMU->FB_STATUS & 1))
        ;

    // C02 already active for SPIm

    CRU->C09_CLK_DIV = 0x017;    // C09=9MHz (divBy8) for PIF (Programming Interface)
    CRU->C09_CLK_GATE |= 0x6;    // enable clock for PIF and FB
    CRU->C08_X1_CLK_GATE |= 0x4; // C08X1 to A0

    PMU->FB_ISOLATION = 1;                                 // ensure isolation
    PMU->GEN_PURPOSE_0 |= PMU_GEN_PURPOSE_0_FB_CFG_ENABLE; // ensure cfg mode
    CFG_CTL_CFG_CTL = 0x0000bdff;                          // enable PIF

    for (int i = 0; i < 50; i++) // wait some time for FPGA reset
        PMU->GEN_PURPOSE_1 = i << 4;

    for (int i = 0; i < (75960 / 4); i++)
        CFG_CTL_CFG_DATA = puiBitstream[i];

    for (int i = 0; i < 50; i++) // wait some time for FPGA reset
        PMU->GEN_PURPOSE_1 = i << 4;

    CFG_CTL_CFG_CTL = 0x0;

    CRU->FB_SW_RESET = 0;
    CRU->FB_MISC_SW_RST_CTL = 0;
    PMU->GEN_PURPOSE_1 = 0x90; // not sure what this is doing...

    PMU->GEN_PURPOSE_0 = 0; // disable config mode

    for (int i = 0; i < 500; i++) // wait some time before releasing LTH_ENB
        PMU->GEN_PURPOSE_1 = i << 4;

    PMU->FB_ISOLATION = 0; // release from isolation

    // Disable driver of pad 19.
    IOMUX->PAD[19] = IOMUX_PAD_E_4MA | IOMUX_PAD_P_PULLDOWN | IOMUX_PAD_OEN_DISABLE | IOMUX_PAD_REN_ENABLE;
}
