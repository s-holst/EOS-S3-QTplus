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

#ifndef __IOMUX_H
#define __IOMUX_H

#include <stdint.h>

#define IOMUX ((IOMUX_typedef *)0x40004C00)

typedef struct
{
    /* 0x000..0x0B4 Source and Electrical Configuration for Pads 0..45
       [1:0] FSEL output function source selection, use IOMUX_PAD_xx_FSEL_*
       [4:3] CSEL output control source selection, use IOMUX_PAD_xx_CSEL_*
       [5] OEN output driver 0=enable <1=disable>
       [7:6] P tri-state control <0=Z> 1=pullup 2=pulldown 3=keeper
       [9:8] E drive strength 0=2mA <1=4mA> 2=8mA 3=12mA
       [10] SR slew rate <0=slow> 1=fast
       [11] REN receive enable <0=disable> 1=enable
       [12] SMT schmitt trigger <0=disable> 1=enable 
       
       Pad43 is MISC->LOCK protected */
    volatile uint32_t PAD[46];
    volatile uint32_t reserved0B8[18];
    volatile uint32_t SDA0_SEL;            // 0x100
    volatile uint32_t SDA1_SEL;            // 0x104
    volatile uint32_t SDA2_SEL;            // 0x108
    volatile uint32_t SCL0_SEL;            // 0x10C
    volatile uint32_t SCL1_SEL;            // 0x110
    volatile uint32_t SCL2_SEL;            // 0x114
    volatile uint32_t SPIs_CLK_SEL;        // 0x118
    volatile uint32_t SPIs_SSn_SEL;        // 0x11C
    volatile uint32_t SPIs_MOSI_SEL;       // 0x120
    volatile uint32_t SPIm_MISO_SEL;       // 0x124
    volatile uint32_t PDM_DATA_SEL;        // 0x128
    volatile uint32_t I2S_DATA_SEL;        // 0x12C
    volatile uint32_t reserved130;         //
    volatile uint32_t UART_RXD_SEL;        // 0x134 [2:0] input from <0=0> 1=pad14 2=pad16 3=pad25 4=pad45
    volatile uint32_t IrDA_Sirin_SEL;      // 0x138
    volatile uint32_t S_INTR_0_SEL;        // 0x13C
    volatile uint32_t S_INTR_1_SEL;        // 0x140
    volatile uint32_t S_INTR_2_SEL;        // 0x144
    volatile uint32_t S_INTR_3_SEL;        // 0x148
    volatile uint32_t S_INTR_4_SEL;        // 0x14C
    volatile uint32_t S_INTR_5_SEL;        // 0x150
    volatile uint32_t S_INTR_6_SEL;        // 0x154
    volatile uint32_t S_INTR_7_SEL;        // 0x158
    volatile uint32_t NUARTCTS_SEL;        // 0x15C
    volatile uint32_t IO_REG_SEL;          // 0x160
    volatile uint32_t reserved164[3];      //
    volatile uint32_t SW_CLK_SEL;          // 0x170
    volatile uint32_t SW_IO_SEL;           // 0x174
    volatile uint32_t reserved178[2];      //
    volatile uint32_t FBIO_SEL_1;          // 0x180
    volatile uint32_t FBIO_SEL_2;          // 0x184
    volatile uint32_t reserved188[2];      //
    volatile uint32_t SPI_SENSOR_MISO_SEL; // 0x190
    volatile uint32_t SPI_SENSOR_MOSI_SEL; // 0x194
    volatile uint32_t reserved198[2];      //
    volatile uint32_t I2S_WD_CLKIN_SEL;    // 0x1A0
    volatile uint32_t I2S_CLKIN_SEL;       // 0x1A4
    volatile uint32_t PDM_STAT_IN_SEL;     // 0x1A8
    volatile uint32_t PDM_CLKIN_SEL;       // 0x1AC
} IOMUX_typedef;

#define IOMUX_PAD_CSEL_OTHER 0x0008
#define IOMUX_PAD_CSEL_FPGA 0x0010
#define IOMUX_PAD_OEN_DISABLE 0x0020
#define IOMUX_PAD_P_PULLUP 0x0040
#define IOMUX_PAD_P_PULLDOWN 0x0080
#define IOMUX_PAD_P_KEEPER 0x00C0
#define IOMUX_PAD_E_2MA 0x0000
#define IOMUX_PAD_E_4MA 0x0100
#define IOMUX_PAD_E_8MA 0x0200
#define IOMUX_PAD_E_12MA 0x0300
#define IOMUX_PAD_SR_FAST 0x0400
#define IOMUX_PAD_REN_ENABLE 0x0800
#define IOMUX_PAD_SMT_ENABLE 0x1000

#define IOMUX_PAD_6_FSEL_GPIO0 0x3
#define IOMUX_PAD_18_FSEL_GPIO4 0x3
#define IOMUX_PAD_21_FSEL_GPIO5 0x3
#define IOMUX_PAD_22_FSEL_GPIO6 0x3

#define IOMUX_UART_RXD_SEL_PAD45 0x0004

#endif