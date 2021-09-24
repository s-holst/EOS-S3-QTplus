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

#include "regs/cru.h"
#include "regs/iomux.h"
#include "regs/uart.h"
#include "regs/misc.h"

int uart_init()
{
    // Start clock C11 = 2MHz
    // Assuming main clock of 72 MHz
    MISC->LOCK_KEY_CTRL = MISC_LOCK_KEY_CTRL_UNLOCK;
    CRU->C11_CLK_GATE |= CRU_C11_CLK_GATE_PATH_0_Msk;
    MISC->LOCK_KEY_CTRL = 0;
    CRU->CLK_CTRL_D_0 = CRU_CLK_CTRL_x_0_DIV_BY(36);

    // Route UART to Pad44(TX) and Pad45(RX)
    IOMUX->PAD[44] = 0x3 | IOMUX_PAD_E_4MA;
    IOMUX->PAD[45] = IOMUX_PAD_OEN_DISABLE | IOMUX_PAD_E_4MA | IOMUX_PAD_REN_ENABLE;
    IOMUX->UART_RXD_SEL = IOMUX_UART_RXD_SEL_PAD45;

    // Configure PL011
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

    return 0;
}

void uart_tx(int c)
{
    while ((UART->TFR & UART_TFR_TX_FIFO_FULL))
        ;
    UART->DR = c;
}

// re-targeting basic write function enables printf.
int _write(int file, char *ptr, int len)
{
    for (int i = 0; i < len; i++)
    {
        uart_tx(ptr[i]);
        if (ptr[i] == '\n')
            uart_tx('\r');
    }
    return len;
}