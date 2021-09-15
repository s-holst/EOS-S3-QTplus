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

#ifndef __IOMUX_H
#define __IOMUX_H

#include <stdint.h>

typedef struct
{
    /* 0x000..0x02D Output Control for Pads 0..45
       [1:0] RW FUNC_SEL chip function output to be connected to the pad
       [4:3] RW CTRL_SEL chip function that controls the pad
       [5]   RW OEN output driver enable: 0=enabled, 1=disabled
       [7:6] RW P tri-state control: 0=Z, 1=pullup, 2=pulldown, 3=keeper
       [9:8] RW E drive strength 0=2mA, 1=4mA, 2=8mA, 3=12mA
       [10]  RW SR slew rate 0=slow, 1=fast
       [11]  RW REN receive enable 1=enable
       [12]  RW SMT schmitt trigger 1=enable
    */
    volatile uint32_t PAD_CTRL[46];
    volatile uint32_t reserved1[18];
    volatile uint32_t SDA0_SEL_REG;                 /* Address offset: 0x100 */
    volatile uint32_t SDA1_SEL_REG;                 /* Address offset: 0x104 */
    volatile uint32_t SDA2_SEL_REG;                 /* Address offset: 0x108 */
    volatile uint32_t SCL0_SEL_REG;                 /* Address offset: 0x10C */
    volatile uint32_t SCL1_SEL_REG;                 /* Address offset: 0x110 */
    volatile uint32_t SCL2_SEL_REG;                 /* Address offset: 0x114 */
    volatile uint32_t SPIs_CLK_SEL;             /* Address offset: 0x118 */
    volatile uint32_t SPIs_SSn_SEL;             /* Address offset: 0x11C */
    volatile uint32_t SPIs_MOSI_SEL;            /* Address offset: 0x120 */
    volatile uint32_t SPIm_MISO_SEL;            /* Address offset: 0x124 */
    volatile uint32_t PDM_DATA_SELE;             /* Address offset: 0x128 */
    volatile uint32_t I2S_DATA_SELECT;             /* Address offset: 0x12C */
    volatile uint32_t reserved2[1];
    volatile uint32_t UART_RXD_SEL;             // 0x134 input control [2:0] 0=0 1=pad14 2=pad16 3=pad25 4=pad45
    volatile uint32_t IrDA_Sirin_SEL;           /* Address offset: 0x138 */
    volatile uint32_t S_INTR_0_SEL_REG;             /* Address offset: 0x13C */
    volatile uint32_t S_INTR_1_SEL_REG;             /* Address offset: 0x140 */
    volatile uint32_t S_INTR_2_SEL;             /* Address offset: 0x144 */
    volatile uint32_t S_INTR_3_SEL;             /* Address offset: 0x148 */
    volatile uint32_t S_INTR_4_SEL;             /* Address offset: 0x14C */
    volatile uint32_t S_INTR_5_SEL;             /* Address offset: 0x150 */
    volatile uint32_t S_INTR_6_SEL;             /* Address offset: 0x154 */
    volatile uint32_t S_INTR_7_SEL;             /* Address offset: 0x158 */
    volatile uint32_t NUARTCTS_SEL;             /* Address offset: 0x15C */
    volatile uint32_t IO_REG_SEL;               /* Address offset: 0x160 */
    volatile uint32_t reserved3[3];
    volatile uint32_t SW_CLK_SEL;               /* Address offset: 0x170 */
    volatile uint32_t SW_IO_SEL;                /* Address offset: 0x174 */
    volatile uint32_t reserved4[2];
    volatile uint32_t FBIO_SEL_1;                 /* Address offset: 0x180 */
    volatile uint32_t FBIO_SEL_2;                 /* Address offset: 0x184 */
    volatile uint32_t reserved5[2];
    volatile uint32_t SPI_SENSOR_MISO_SEL;	/* Address offset: 0x190 */
    volatile uint32_t SPI_SENSOR_MOSI_SEL;	/* Address offset: 0x194 */
    volatile uint32_t reserved6[2];
    volatile uint32_t I2S_WD_CLKIN_SEL;	/* Address offset: 0x1A0 */
    volatile uint32_t I2S_CLKIN_SEL;	/* Address offset: 0x1A4 */
    volatile uint32_t PDM_STAT_IN_SEL;	/* Address offset: 0x1A8 */
    volatile uint32_t PDM_CLKIN_SEL;	/* Address offset: 0x1AC */
} IOMUX_typedef;

#define IOMUX_BASE (0x40004C00)
#define IOMUX ((IOMUX_typedef*) IOMUX_BASE)


#define IOMUX_PAD_CTRL_SEL_OTHER    ((uint32_t) (0x00000008))
#define IOMUX_PAD_CTRL_SEL_FPGA     ((uint32_t) (0x00000010))
#define IOMUX_PAD_CTRL_OEN_DISABLE  ((uint32_t) (0x00000020))
#define IOMUX_PAD_CTRL_P_PULLUP     ((uint32_t) (0x00000040))
#define IOMUX_PAD_CTRL_P_PULLDOWN   ((uint32_t) (0x00000080))
#define IOMUX_PAD_CTRL_P_KEEPER     ((uint32_t) (0x000000C0))
#define IOMUX_PAD_CTRL_E_2MA        ((uint32_t) (0x00000000))
#define IOMUX_PAD_CTRL_E_4MA        ((uint32_t) (0x00000100))
#define IOMUX_PAD_CTRL_E_8MA        ((uint32_t) (0x00000200))
#define IOMUX_PAD_CTRL_E_12MA       ((uint32_t) (0x00000300))
#define IOMUX_PAD_CTRL_SR_FAST      ((uint32_t) (0x00000400))
#define IOMUX_PAD_CTRL_REN_ENABLE   ((uint32_t) (0x00000800))
#define IOMUX_PAD_CTRL_SMT_ENABLE   ((uint32_t) (0x00001000))

#define IOMUX_UART_RXD_SEL_PAD45    ((uint32_t) (0x00000004))

#endif