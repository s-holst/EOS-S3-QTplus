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

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#include "pmu.h"
#include "cru.h"
#include "iomux.h"
#include "ffe.h"
#include "intr.h"
#include "uart.h"
#include "misc.h"
#include "aip.h"

void dbg_ch(int c) {
    while ((UART->UART_TFR & UART_TFR_TX_FIFO_FULL)) {}
    UART->UART_DR = c;
    if (c=='\n') {
        while ((UART->UART_TFR & UART_TFR_TX_FIFO_FULL)) {}
        UART->UART_DR = '\r';
    }
}

void dbg_str(const char *s) {
    while(*s) { dbg_ch(*s++); }
}

char strbuf[1024];
void dbg_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf((char * restrict)&strbuf, 1024, format, args);
    va_end(args);
    dbg_str(strbuf);
}

int wb_write(uint8_t ucAddr, uint8_t ucData) {
    if (FFE->CSR & (FFE_CSR_BUSY|FFE_CSR_MASTER_START)) return -1;
    FFE->ADDR = ucAddr;
    FFE->WDATA = ucData;
    FFE->CSR = FFE_CSR_I2C0MUX_SEL_WBMASTER|FFE_CSR_MASTER_WR_EN|FFE_CSR_MASTER_START|FFE_CSR_MUX_WB_SM;
    return 0;
}

int wb_read(uint8_t ucAddr, uint8_t *pucData) {
    FFE->ADDR = ucAddr;
    FFE->CSR = FFE_CSR_I2C0MUX_SEL_WBMASTER|FFE_CSR_MASTER_START|FFE_CSR_MUX_WB_SM;
    while (FFE->CSR & (FFE_CSR_BUSY|FFE_CSR_MASTER_START)) {}
    *pucData = FFE->RDATA;
    return 0;
}

int i2c_write_byte(uint8_t ucData, uint8_t ucFlags) {
    uint8_t ucStatus = 0;

    if (wb_write(WB_I2C_TXRX, ucData)) return -1;
    if (wb_write(WB_I2C_CSR, WB_I2C_CSR_WRITE_Msk | ucFlags)) return -2;
    do {wb_read(WB_I2C_CSR, &ucStatus);} while (ucStatus & WB_I2C_CSR_TIP_Msk);
    if (ucStatus & WB_I2C_CSR_RXACK_Msk) return -3;

    return 0;
}

int i2c_read_byte(uint8_t *pucData, uint8_t ucFlags) {
    uint8_t ucStatus = 0;

    if (wb_write(WB_I2C_CSR, WB_I2C_CSR_READ_Msk | ucFlags)) return -1;
    do {wb_read(WB_I2C_CSR, &ucStatus);} while (ucStatus & WB_I2C_CSR_TIP_Msk);
    wb_read(WB_I2C_TXRX, pucData);

    return 0;
}

int i2c_write_regs(uint8_t ucDevAddr, uint8_t ucRegAddr, uint8_t *pucData, uint32_t uiLength) {
    if (!ucDevAddr || !pucData || !uiLength) return -1;
    if (i2c_write_byte(ucDevAddr<<1, WB_I2C_CSR_START_Msk)) return -2;
    if (i2c_write_byte(ucRegAddr, 0)) return -3;    
    while(--uiLength) {
        if (i2c_write_byte(*pucData++, 0)) return -3;
    }
    if (i2c_write_byte(*pucData++, WB_I2C_CSR_STOP_Msk)) return -3;

    return 0;
}

int i2c_write_reg(uint8_t ucDevAddr, uint8_t ucRegAddr, uint8_t ucData) {
    return i2c_write_regs(ucDevAddr, ucRegAddr, &ucData, 1);
}

int i2c_read_regs(uint8_t ucDevAddr, uint8_t ucRegAddr, uint8_t *pucData, uint32_t uiLength) {
    if (!ucDevAddr || !pucData || !uiLength) return -1;
    if (i2c_write_byte(ucDevAddr<<1, WB_I2C_CSR_START_Msk)) return -2;
    if (i2c_write_byte(ucRegAddr, 0)) return -3;
    if (i2c_write_byte((ucDevAddr<<1)|1, WB_I2C_CSR_START_Msk)) return -4;
    while(--uiLength) {
        if (i2c_read_byte(pucData++, 0)) return -5;
    }
    if (i2c_read_byte(pucData, WB_I2C_CSR_STOP_Msk | WB_I2C_CSR_NACK_Msk)) return -6;

    return 0;
}

int main(void) {

    // FFE power up for I2C
    PMU->FFE_FB_PF_SW_WU |= PMU_FFE_FB_PF_SW_WU_FFE_WU_Msk;
    while(!(PMU->FFE_STATUS & 1));

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
    IOMUX->PAD_CTRL[44] = 0x3 | IOMUX_PAD_CTRL_E_4MA;
    IOMUX->PAD_CTRL[45] = IOMUX_PAD_CTRL_OEN_DISABLE|IOMUX_PAD_CTRL_E_4MA|IOMUX_PAD_CTRL_REN_ENABLE;
    IOMUX->UART_RXD_SEL = IOMUX_UART_RXD_SEL_PAD45;

    // Route I2C to Pad0 and Pad1
    IOMUX->PAD_CTRL[0] = IOMUX_PAD_CTRL_SEL_OTHER|IOMUX_PAD_CTRL_P_PULLUP|IOMUX_PAD_CTRL_E_4MA|IOMUX_PAD_CTRL_REN_ENABLE;
    IOMUX->PAD_CTRL[1] = IOMUX_PAD_CTRL_SEL_OTHER|IOMUX_PAD_CTRL_P_PULLUP|IOMUX_PAD_CTRL_E_4MA|IOMUX_PAD_CTRL_REN_ENABLE;
    IOMUX->SDA0_SEL_REG = 1;
    IOMUX->SCL0_SEL_REG = 1;
	
    // Configure PL011 UART
    UART->UART_CR = 0;      // first disable UART
    UART->UART_LCR_H = 0;
	UART->UART_IMSC = 0;    // disable interrupts
	UART->UART_RSR = 0;
	UART->UART_ILPR = 0;
	UART->UART_ICR = 0x7ff; // clear all interrupts
    UART->UART_IBRD = 1;    // C11Hz=2e6 baudrate=115200
	UART->UART_FBRD = 5;
    UART->UART_LCR_H = UART_LCR_WLEN_8_BITS|UART_LCR_ENABLE_FIFO;
    UART->UART_IFLS = UART_IFLS_RX_1_8_FULL|UART_IFLS_TX_1_2_FULL;
    UART->UART_CR = UART_CR_TX_ENABLE|UART_CR_RX_ENABLE|UART_CR_UART_ENABLE;  // finally, enable UART
    
    // Configure I2C frequency scaling factor s
    // I2Cfreq = C08X1Hz / (5*(s+1)+(int(s/4)*2+5))
    // Here: 9 MHz / (5*(15+1)+(int(15/4)*2+5)) = 99kHz
    wb_write(WB_I2C_PRELO, 15);
    wb_write(WB_I2C_MCR, WB_I2C_MCR_EN_Msk);

    // Initialize LIS2D
    i2c_write_reg(0x18, 0x23, 0x80);
    i2c_write_reg(0x18, 0x20, 0x57);
    i2c_write_reg(0x18, 0x1f, 0xC0);
    
    dbg_str("\n\nhello\n\n");
    
    uint32_t counter;
    uint8_t b[10];
    
    while(1) {
        if (!(counter++ & 0xfffff)) {
            i2c_read_regs(0x18, 0x80 | 0x28, b, 6);
            int32_t x = ((b[0]>>6) & 0x3) | ((int32_t)((int8_t)b[1]))<<2;
            int32_t y = ((b[2]>>6) & 0x3) | ((int32_t)((int8_t)b[3]))<<2;
            int32_t z = ((b[4]>>6) & 0x3) | ((int32_t)((int8_t)b[5]))<<2;
            dbg_printf("%6d %6d %6d\n", x, y, z);
        }
    }

    return 0;
}