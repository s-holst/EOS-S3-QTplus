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
#include <stdio.h>
#include <stdarg.h>

#include "regs/pmu.h"
#include "regs/cru.h"
#include "regs/iomux.h"
#include "regs/ffe.h"
#include "regs/intr.h"
#include "regs/uart.h"
#include "regs/misc.h"
#include "regs/aip.h"

void dbg_ch(int c)
{
    while ((UART->TFR & UART_TFR_TX_FIFO_FULL))
        ;
    UART->DR = c;
    if (c == '\n')
    {
        while ((UART->TFR & UART_TFR_TX_FIFO_FULL))
            ;
        UART->DR = '\r';
    }
}

void dbg_str(const char *s)
{
    while (*s)
    {
        dbg_ch(*s++);
    }
}

char strbuf[1024];
void dbg_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf((char *restrict)&strbuf, 1024, format, args);
    va_end(args);
    dbg_str(strbuf);
}

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

int main(void)
{
    // FFE power up for I2C
    PMU->FFE_FB_PF_SW_WU |= PMU_FFE_FB_PF_SW_WU_FFE_WU_Msk;
    while (!(PMU->FFE_STATUS & 1))
        ;

    // Set main clock to 72 MHz
    AIP->OSC_CTRL_1 = 2194;
    CRU->CLK_CTRL_A_0 = 0;

    // Start clock C11 = 2MHz for UART
    MISC->LOCK_KEY_CTRL = MISC_LOCK_KEY_CTRL_UNLOCK;
    CRU->C11_CLK_GATE |= CRU_C11_CLK_GATE_PATH_0_Msk;
    MISC->LOCK_KEY_CTRL = 0;
    CRU->CLK_CTRL_D_0 = 0x222;

    // Start clock C08X4 = 36 MHz and C08X1 = 9 MHz for I2C
    CRU->CLK_CTRL_C_0 = CRU_CLK_CTRL_x_0_DIV_BY_2;
    CRU->C01_CLK_GATE |= CRU_C01_CLK_GATE_PATH_3_Msk;
    CRU->C08_X1_CLK_GATE |= CRU_C08_X1_CLK_GATE_PATH_0_Msk;
    CRU->C08_X4_CLK_GATE |= CRU_C08_X4_CLK_GATE_PATH_0_Msk;

    // Route UART to Pad44(TX) and Pad45(RX)
    IOMUX->PAD[44] = 0x3 | IOMUX_PAD_E_4MA;
    IOMUX->PAD[45] = IOMUX_PAD_OEN_DISABLE | IOMUX_PAD_E_4MA | IOMUX_PAD_REN_ENABLE;
    IOMUX->UART_RXD_SEL = IOMUX_UART_RXD_SEL_PAD45;

    // Route I2C to Pad0 and Pad1
    IOMUX->PAD[0] = IOMUX_PAD_CSEL_OTHER | IOMUX_PAD_P_PULLUP | IOMUX_PAD_E_4MA | IOMUX_PAD_REN_ENABLE;
    IOMUX->PAD[1] = IOMUX_PAD_CSEL_OTHER | IOMUX_PAD_P_PULLUP | IOMUX_PAD_E_4MA | IOMUX_PAD_REN_ENABLE;
    IOMUX->SDA0_SEL = 1;
    IOMUX->SCL0_SEL = 1;

    IOMUX->PAD[6] = IOMUX_PAD_6_FSEL_GPIO0 | IOMUX_PAD_OEN_DISABLE | IOMUX_PAD_REN_ENABLE;
    IOMUX->PAD[18] = IOMUX_PAD_18_FSEL_GPIO4 | IOMUX_PAD_E_4MA; // Route GPIO4 -> Blue LED on Pad 18
    IOMUX->PAD[21] = IOMUX_PAD_21_FSEL_GPIO5 | IOMUX_PAD_E_4MA; // Route GPIO5 -> Green LED on Pad 21
    IOMUX->PAD[22] = IOMUX_PAD_22_FSEL_GPIO6 | IOMUX_PAD_E_4MA; // Route GPIO6 -> Red LED on Pad 22

    // Configure PL011 UART
    UART->CR = 0; // first, disable UART
    UART->LCR_H = 0;
    UART->IMSC = 0; // disable interrupts
    UART->RSR = 0;
    UART->ILPR = 0;
    UART->ICR = UART_intr_ALL_Msk; // clear all interrupts
    UART->IBRD = 1;                // C11Hz=2e6 baudrate=115200
    UART->FBRD = 5;
    UART->LCR_H = UART_LCR_WLEN_8_BITS | UART_LCR_ENABLE_FIFO;
    UART->IFLS = UART_IFLS_RX_1_8_FULL | UART_IFLS_TX_1_2_FULL;
    UART->CR = UART_CR_TX_ENABLE | UART_CR_RX_ENABLE | UART_CR_UART_ENABLE; // finally, enable UART

    // Configure I2C frequency scaling factor s
    // I2Cfreq = C08X1Hz / (5*(s+1)+(int(s/4)*2+5))
    // Here: 9 MHz / (5*(15+1)+(int(15/4)*2+5)) = 99kHz
    wb_write(WB_I2C_PRELO, 15);
    wb_write(WB_I2C_MCR, WB_I2C_MCR_EN_Msk);

    dbg_str("\n\nInitializing LIS2DH12...\n");
    i2c_write_reg(0x18, 0x23, 0x80);
    i2c_write_reg(0x18, 0x20, 0x57);
    i2c_write_reg(0x18, 0x1f, 0xC0);

    uint32_t counter;
    uint8_t b[10];
    uint8_t led_state, led_oldstate;

    while (1)
    {
        counter++;

        // cycle through all combinations on GPIO4, GPIO5, GPIO6
        led_state = ((counter >> 21) & 0x07) << 4;
        if (led_state != led_oldstate)
        {
            MISC->IO_OUTPUT |= led_state;
            MISC->IO_OUTPUT &= led_state | ~(0x07 << 4);
            led_oldstate = led_state;
        }

        if (!(counter & 0x8ffff))
        {
            i2c_read_regs(0x18, 0x80 | 0x28, b, 6);
            int32_t x = ((b[0] >> 6) & 0x3) | ((int32_t)((int8_t)b[1])) << 2;
            int32_t y = ((b[2] >> 6) & 0x3) | ((int32_t)((int8_t)b[3])) << 2;
            int32_t z = ((b[4] >> 6) & 0x3) | ((int32_t)((int8_t)b[5])) << 2;
            dbg_printf("X %6d Y %6d Z %6d USR %d\n", x, y, z, (~MISC->IO_INPUT) & 1);
        }
    }

    return 0;
}