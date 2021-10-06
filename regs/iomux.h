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
       [4:3] CSEL output control source selection <0=A0reg> 1=others 2=fabric (some pad's default is 1)
       [5] OEN output driver 0=enable <1=disable>
       [7:6] P tri-state control <0=nopull> 1=pullup 2=pulldown 3=keeper
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
    volatile uint32_t FBIO_SEL_1;          // 0x180 [31:0] input from <0=0> <1=pad0..31>
    volatile uint32_t FBIO_SEL_2;          // 0x184 [13:0] input from <0=0> <1=pad32..45>
    volatile uint32_t reserved188[2];      //
    volatile uint32_t SPI_SENSOR_MISO_SEL; // 0x190
    volatile uint32_t SPI_SENSOR_MOSI_SEL; // 0x194
    volatile uint32_t reserved198[2];      //
    volatile uint32_t I2S_WD_CLKIN_SEL;    // 0x1A0
    volatile uint32_t I2S_CLKIN_SEL;       // 0x1A4
    volatile uint32_t PDM_STAT_IN_SEL;     // 0x1A8
    volatile uint32_t PDM_CLKIN_SEL;       // 0x1AC
} IOMUX_typedef;

#define IOMUX_PAD_CSEL_A0REG 0x0000
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

// output function source selection (chip function -> pad)

#define IOMUX_PAD_0_FSEL_SCL0 0
#define IOMUX_PAD_0_FSEL_FBIO0 1

#define IOMUX_PAD_1_FSEL_SDA0 0
#define IOMUX_PAD_1_FSEL_FBIO1 1

#define IOMUX_PAD_2_FSEL_FBIO2 0
#define IOMUX_PAD_2_FSEL_SPI_SENSOR_SSn2 1
#define IOMUX_PAD_2_FSEL_DEBUG_MON0 2
#define IOMUX_PAD_2_FSEL_BATT_MON 3

#define IOMUX_PAD_3_FSEL_FBIO3 0

#define IOMUX_PAD_4_FSEL_FBIO4 0
#define IOMUX_PAD_4_FSEL_SPI_SENSOR_SSn3 1
#define IOMUX_PAD_4_FSEL_DEBUG_MON1 2
#define IOMUX_PAD_4_FSEL_SDA1_DPU 3

#define IOMUX_PAD_5_FSEL_FBIO5 0
#define IOMUX_PAD_5_FSEL_SPI_SENSOR_SSn4 1
#define IOMUX_PAD_5_FSEL_DEBUG_MON2 2
#define IOMUX_PAD_5_FSEL_SDA0_DPU 3

#define IOMUX_PAD_6_FSEL_FBIO6 0
#define IOMUX_PAD_6_FSEL_SPI_SENSOR_MOSI 1
#define IOMUX_PAD_6_FSEL_DEBUG_MON3 2
#define IOMUX_PAD_6_FSEL_GPIO0 3

#define IOMUX_PAD_7_FSEL_FBIO7 0
#define IOMUX_PAD_7_FSEL_SPI_SENSOR_SSn5 1
#define IOMUX_PAD_7_FSEL_DEBUG_MON4 2
#define IOMUX_PAD_7_FSEL_SWV 3

#define IOMUX_PAD_8_FSEL_FBIO8 0
#define IOMUX_PAD_8_FSEL_PDM_CKO 1
#define IOMUX_PAD_8_FSEL_I2S_CKO 2
#define IOMUX_PAD_8_FSEL_IRDA_SIROUT 3

#define IOMUX_PAD_9_FSEL_FBIO9 0
#define IOMUX_PAD_9_FSEL_SPI_SENSOR_SSn1 1
#define IOMUX_PAD_9_FSEL_I2S_WD_CKO 2
#define IOMUX_PAD_9_FSEL_GPIO1 3

#define IOMUX_PAD_10_FSEL_FBIO10 0
#define IOMUX_PAD_10_FSEL_SPI_SENSOR_CLK 1
#define IOMUX_PAD_10_FSEL_RESERVE 2
#define IOMUX_PAD_10_FSEL_SWV 3

#define IOMUX_PAD_11_FSEL_FBIO11 0
#define IOMUX_PAD_11_FSEL_SPI_SENSOR_SSn6 1
#define IOMUX_PAD_11_FSEL_DEBUG_MON5 2
#define IOMUX_PAD_11_FSEL_GPIO2 3

#define IOMUX_PAD_12_FSEL_FBIO12 0
#define IOMUX_PAD_12_FSEL_SPI_SENSOR_SSn7 1
#define IOMUX_PAD_12_FSEL_DEBUG_MON6 2
#define IOMUX_PAD_12_FSEL_IRDA_SIROUT 3

#define IOMUX_PAD_13_FSEL_FBIO13 0
#define IOMUX_PAD_13_FSEL_SPI_SENSOR_SSn8 1
#define IOMUX_PAD_13_FSEL_DEBUG_MON7 2
#define IOMUX_PAD_13_FSEL_SWV 3

#define IOMUX_PAD_14_FSEL_FBIO14 0
#define IOMUX_PAD_14_FSEL_IRDA_SIROUT 1
#define IOMUX_PAD_14_FSEL_SCL1 2
#define IOMUX_PAD_14_FSEL_GPIO3 3

#define IOMUX_PAD_15_FSEL_SW_DP_IO 0
#define IOMUX_PAD_15_FSEL_FBIO15 1
#define IOMUX_PAD_15_FSEL_SDA1 2
#define IOMUX_PAD_15_FSEL_UART_TXD 3

#define IOMUX_PAD_16_FSEL_FBIO16 0

#define IOMUX_PAD_17_FSEL_SPIs_MISO 0
#define IOMUX_PAD_17_FSEL_FBIO17 1

#define IOMUX_PAD_18_FSEL_FBIO18 0
#define IOMUX_PAD_18_FSEL_SWV 1
#define IOMUX_PAD_18_FSEL_DEBUG_MON0 2
#define IOMUX_PAD_18_FSEL_GPIO4 3

#define IOMUX_PAD_19_FSEL_FBIO19 0
#define IOMUX_PAD_19_FSEL_nUARTRTS 1

#define IOMUX_PAD_20_FSEL_FBIO20 0
#define IOMUX_PAD_20_FSEL_UART_TXD 1

#define IOMUX_PAD_21_FSEL_FBIO21 0
#define IOMUX_PAD_21_FSEL_nUARTRTS 1
#define IOMUX_PAD_21_FSEL_DEBUG_MON1 2
#define IOMUX_PAD_21_FSEL_GPIO5 3

#define IOMUX_PAD_22_FSEL_FBIO22 0
#define IOMUX_PAD_22_FSEL_IRDA_SIROUT 1
#define IOMUX_PAD_22_FSEL_DEBUG_MON2 2
#define IOMUX_PAD_22_FSEL_GPIO6 3

#define IOMUX_PAD_23_FSEL_FBIO23 0
#define IOMUX_PAD_23_FSEL_SPIm_SSn2 1
#define IOMUX_PAD_23_FSEL_SWV 2
#define IOMUX_PAD_23_FSEL_GPIO7 3

#define IOMUX_PAD_24_FSEL_FBIO24 0
#define IOMUX_PAD_24_FSEL_AP_I2S_DOUT 1
#define IOMUX_PAD_24_FSEL_UART_TXD 2
#define IOMUX_PAD_24_FSEL_GPIO0 3

#define IOMUX_PAD_25_FSEL_FBIO25 0
#define IOMUX_PAD_25_FSEL_SPIm_SSn3 1
#define IOMUX_PAD_25_FSEL_SWV 2
#define IOMUX_PAD_25_FSEL_IRDA_SIROUT 3

#define IOMUX_PAD_26_FSEL_FBIO26 0
#define IOMUX_PAD_26_FSEL_SPI_SENSOR_SSn4 1
#define IOMUX_PAD_26_FSEL_DEBUG_MON3 2
#define IOMUX_PAD_26_FSEL_GPIO1 3

#define IOMUX_PAD_27_FSEL_FBIO27 0
#define IOMUX_PAD_27_FSEL_SPI_SENSOR_SSn5 1
#define IOMUX_PAD_27_FSEL_DEBUG_MON4 2
#define IOMUX_PAD_27_FSEL_SPIm_SSn2 3

#define IOMUX_PAD_28_FSEL_FBIO28 0
#define IOMUX_PAD_28_FSEL_SPI_SENSOR_MOSI 1
#define IOMUX_PAD_28_FSEL_DEBUG_MON5 2
#define IOMUX_PAD_28_FSEL_GPIO2 3

#define IOMUX_PAD_29_FSEL_FBIO29 0
#define IOMUX_PAD_29_FSEL_PDM_CKO 1
#define IOMUX_PAD_29_FSEL_I2S_CKO 2
#define IOMUX_PAD_29_FSEL_IRDA_SIROUT 3

#define IOMUX_PAD_30_FSEL_FBIO30 0
#define IOMUX_PAD_30_FSEL_SPI_SENSOR_SSn1 1
#define IOMUX_PAD_30_FSEL_I2S_WD_CKO 2
#define IOMUX_PAD_30_FSEL_GPIO3 3

#define IOMUX_PAD_31_FSEL_FBIO31 0
#define IOMUX_PAD_31_FSEL_SPI_SENSOR_CLK 1
#define IOMUX_PAD_31_FSEL_RESERVED 2
#define IOMUX_PAD_31_FSEL_GPIO4 3

#define IOMUX_PAD_32_FSEL_FBIO32 0
#define IOMUX_PAD_32_FSEL_SPI_SENSOR_SSn5 1
#define IOMUX_PAD_32_FSEL_DEBUG_MON6 2
#define IOMUX_PAD_32_FSEL_SDA1 3

#define IOMUX_PAD_33_FSEL_FBIO33 0
#define IOMUX_PAD_33_FSEL_SPI_SENSOR_SSn6 1
#define IOMUX_PAD_33_FSEL_DEBUG_MON7 2
#define IOMUX_PAD_33_FSEL_SCL1 3

#define IOMUX_PAD_34_FSEL_SPIm_CLK 0
#define IOMUX_PAD_34_FSEL_FBIO34 1
#define IOMUX_PAD_34_FSEL_AP_PDM_STAT_O 2
#define IOMUX_PAD_34_FSEL_DEBUG_MON0 3

#define IOMUX_PAD_35_FSEL_FBIO35 0
#define IOMUX_PAD_35_FSEL_SPIm_SSn3 1
#define IOMUX_PAD_35_FSEL_SPI_SENSOR_SSn7 2
#define IOMUX_PAD_35_FSEL_DEBUG_MON1 3

#define IOMUX_PAD_36_FSEL_SPIm_MISO 0
#define IOMUX_PAD_36_FSEL_FBIO36 0
#define IOMUX_PAD_36_FSEL_SWV 1
#define IOMUX_PAD_36_FSEL_SPI_SENSOR_SSn2 2
#define IOMUX_PAD_36_FSEL_GPIO5 3

#define IOMUX_PAD_37_FSEL_FBIO37 0
#define IOMUX_PAD_37_FSEL_SDA2_DPU 1
#define IOMUX_PAD_37_FSEL_SPI_SENSOR_SSn8 2
#define IOMUX_PAD_37_FSEL_DEBUG_MON2 3

#define IOMUX_PAD_38_FSEL_SPIm_MOSI 0
#define IOMUX_PAD_38_FSEL_FBIO38 1
#define IOMUX_PAD_38_FSEL_DEBUG_MON3 2
#define IOMUX_PAD_38_FSEL_GPIO6 3

#define IOMUX_PAD_39_FSEL_SPIm_SSn1 0
#define IOMUX_PAD_39_FSEL_FBIO39 1
#define IOMUX_PAD_39_FSEL_AP_PDM_IO 2
#define IOMUX_PAD_39_FSEL_DEBUG_MON4 3

#define IOMUX_PAD_40_FSEL_FBIO40 0
#define IOMUX_PAD_40_FSEL_SCL2 1
#define IOMUX_PAD_40_FSEL_DEBUG_MON5 2
#define IOMUX_PAD_40_FSEL_RESERVED 3

#define IOMUX_PAD_41_FSEL_FBIO41 0
#define IOMUX_PAD_41_FSEL_SDA2 1
#define IOMUX_PAD_41_FSEL_DEBUG_MON6 2
#define IOMUX_PAD_41_FSEL_IRDA_SIROUT 3

#define IOMUX_PAD_42_FSEL_FBIO42 0
#define IOMUX_PAD_42_FSEL_SWV 1
#define IOMUX_PAD_42_FSEL_DEBUG_MON7 2
#define IOMUX_PAD_42_FSEL_SDA1_DPU 3

#define IOMUX_PAD_43_FSEL_AP_INTR 0
#define IOMUX_PAD_43_FSEL_FBIO43 1

#define IOMUX_PAD_44_FSEL_SW_DP_IO 0
#define IOMUX_PAD_44_FSEL_FBIO44 1
#define IOMUX_PAD_44_FSEL_SDA1 2
#define IOMUX_PAD_44_FSEL_UART_TXD 3

#define IOMUX_PAD_45_FSEL_FBIO45 0
#define IOMUX_PAD_45_FSEL_IRDA_SIROUT 1
#define IOMUX_PAD_45_FSEL_SCL1 2
#define IOMUX_PAD_45_FSEL_GPIO7 3

// input function destination selection (pad -> chip function)

#define IOMUX_SDA0_SEL_CONST1 0
#define IOMUX_SDA0_SEL_PAD1 1

#define IOMUX_SCL0_SEL_CONST1 0
#define IOMUX_SCL0_SEL_PAD0 1

#define IOMUX_UART_RXD_SEL_PAD45 4

#define IOMUX_SPIm_MISO_SEL_PAD36 0
#define IOMUX_SPIm_MISO_SEL_CONST0 1

#define IOMUX_S_INTR_0_SEL_PAD3 1

#endif