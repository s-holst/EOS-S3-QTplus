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

#include <stdint.h>

#include "regs/pmu.h"
#include "regs/cru.h"
#include "regs/iomux.h"
#include "regs/ffe.h"

int wb_write(uint8_t ucAddr, uint8_t ucData)
{
    while (FFE->CSR & (FFE_CSR_BUSY | FFE_CSR_MASTER_START))
        ;
    FFE->ADDR = ucAddr;
    FFE->WDATA = ucData;
    FFE->CSR = FFE_CSR_I2C0MUX_SEL_WBMASTER | FFE_CSR_MASTER_WR_EN | FFE_CSR_MASTER_START | FFE_CSR_MUX_WB_SM;
    return 0;
}

int wb_read(uint8_t ucAddr, uint8_t *pucData)
{
    while (FFE->CSR & (FFE_CSR_BUSY | FFE_CSR_MASTER_START))
        ;
    FFE->ADDR = ucAddr;
    FFE->CSR = FFE_CSR_I2C0MUX_SEL_WBMASTER | FFE_CSR_MASTER_START | FFE_CSR_MUX_WB_SM;
    while (FFE->CSR & (FFE_CSR_BUSY | FFE_CSR_MASTER_START))
        ;
    *pucData = FFE->RDATA;
    return 0;
}

int i2c_init()
{
    // ensure FFE power up
    PMU->FFE_FB_PF_SW_WU |= PMU_FFE_FB_PF_SW_WU_FFE_WU_Msk;
    while (!(PMU->FFE_STATUS & 1))
        ;

    // Start clock C08X4 = 36 MHz and C08X1 = 9 MHz
    // Assuming main clock is 72MHz
    CRU->CLK_CTRL_C_0 = CRU_CLK_CTRL_x_0_DIV_BY(2);
    CRU->C01_CLK_GATE |= CRU_C01_CLK_GATE_PATH_3_Msk;
    CRU->C08_X1_CLK_GATE |= CRU_C08_X1_CLK_GATE_PATH_0_Msk;
    CRU->C08_X4_CLK_GATE |= CRU_C08_X4_CLK_GATE_PATH_0_Msk;

    // Route I2C to Pad0 and Pad1
    IOMUX->PAD[0] = IOMUX_PAD_CSEL_OTHER | IOMUX_PAD_P_PULLUP | IOMUX_PAD_E_4MA | IOMUX_PAD_REN_ENABLE;
    IOMUX->PAD[1] = IOMUX_PAD_CSEL_OTHER | IOMUX_PAD_P_PULLUP | IOMUX_PAD_E_4MA | IOMUX_PAD_REN_ENABLE;
    IOMUX->SDA0_SEL = 1;
    IOMUX->SCL0_SEL = 1;

    // Configure I2C frequency scaling factor s
    // I2Cfreq = C08X1Hz / (5*(s+1)+(int(s/4)*2+5))
    // Here: 9 MHz / (5*(15+1)+(int(15/4)*2+5)) = 99kHz
    wb_write(WB_I2C_PRELO, 15);
    wb_write(WB_I2C_MCR, WB_I2C_MCR_EN_Msk);

    return 0;
}

int i2c_write_byte(uint8_t ucData, uint8_t ucFlags)
{
    uint8_t ucStatus = 0;

    if (wb_write(WB_I2C_TXRX, ucData))
        return -1;
    if (wb_write(WB_I2C_CSR, WB_I2C_CSR_WRITE_Msk | ucFlags))
        return -2;
    do
    {
        wb_read(WB_I2C_CSR, &ucStatus);
    } while (ucStatus & WB_I2C_CSR_TIP_Msk);
    if (ucStatus & WB_I2C_CSR_RXACK_Msk)
        return -3;

    return 0;
}

int i2c_read_byte(uint8_t *pucData, uint8_t ucFlags)
{
    uint8_t ucStatus = 0;

    if (wb_write(WB_I2C_CSR, WB_I2C_CSR_READ_Msk | ucFlags))
        return -1;
    do
    {
        wb_read(WB_I2C_CSR, &ucStatus);
    } while (ucStatus & WB_I2C_CSR_TIP_Msk);
    wb_read(WB_I2C_TXRX, pucData);

    return 0;
}

int i2c_write_regs(uint8_t ucDevAddr, uint8_t ucRegAddr, uint8_t *pucData, uint32_t uiLength)
{
    if (!ucDevAddr || !pucData || !uiLength)
        return -1;
    if (i2c_write_byte(ucDevAddr << 1, WB_I2C_CSR_START_Msk))
        return -2;
    if (i2c_write_byte(ucRegAddr, 0))
        return -3;
    while (--uiLength)
    {
        if (i2c_write_byte(*pucData++, 0))
            return -3;
    }
    if (i2c_write_byte(*pucData++, WB_I2C_CSR_STOP_Msk))
        return -3;

    return 0;
}

int i2c_write_reg(uint8_t ucDevAddr, uint8_t ucRegAddr, uint8_t ucData)
{
    return i2c_write_regs(ucDevAddr, ucRegAddr, &ucData, 1);
}

int i2c_read_regs(uint8_t ucDevAddr, uint8_t ucRegAddr, uint8_t *pucData, uint32_t uiLength)
{
    if (!ucDevAddr || !pucData || !uiLength)
        return -1;
    if (i2c_write_byte(ucDevAddr << 1, WB_I2C_CSR_START_Msk))
        return -2;
    if (i2c_write_byte(ucRegAddr, 0))
        return -3;
    if (i2c_write_byte((ucDevAddr << 1) | 1, WB_I2C_CSR_START_Msk))
        return -4;
    while (--uiLength)
    {
        if (i2c_read_byte(pucData++, 0))
            return -5;
    }
    if (i2c_read_byte(pucData, WB_I2C_CSR_STOP_Msk | WB_I2C_CSR_NACK_Msk))
        return -6;

    return 0;
}