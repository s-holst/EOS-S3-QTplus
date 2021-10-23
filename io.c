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
#include "regs/misc.h"
#include "regs/cru.h"
#include "regs/adc.h"

void io_init()
{
    IOMUX->PAD[6] = IOMUX_PAD_6_FSEL_GPIO0 | IOMUX_PAD_OEN_DISABLE |
                    IOMUX_PAD_REN_ENABLE | IOMUX_PAD_SMT_ENABLE; // USR button
    IOMUX->PAD[18] = IOMUX_PAD_18_FSEL_GPIO4 | IOMUX_PAD_E_4MA;  // Route GPIO4 -> Blue LED on Pad 18
    IOMUX->PAD[21] = IOMUX_PAD_21_FSEL_GPIO5 | IOMUX_PAD_E_4MA;  // Route GPIO5 -> Green LED on Pad 21
    IOMUX->PAD[22] = IOMUX_PAD_22_FSEL_GPIO6 | IOMUX_PAD_E_4MA;  // Route GPIO6 -> Red LED on Pad 22

    // Output high on Pad 26 for battery voltage monitoring
    IOMUX->PAD[26] = IOMUX_PAD_26_FSEL_GPIO1 | IOMUX_PAD_E_4MA;
    MISC->IO_OUTPUT |= (1 << 1);

    // Enable ADC
    CRU->CLK_CTRL_H_0 = CRU_CLK_CTRL_x_0_DIV_BY(72); // C19 = 1MHz
    CRU->CLK_DIVIDER_CLK_GATING |= (1 << 7);
    CRU->C19_CLK_GATE |= 1;
    ADC->CTRL &= ~ADC_CTRL_START_Msk; // stop conversions
}

void io_set_red(uint8_t ucOn)
{
    if (ucOn)
        MISC->IO_OUTPUT |= (1 << 6);
    else
        MISC->IO_OUTPUT &= ~(1 << 6);
}

void io_set_green(uint8_t ucOn)
{
    if (ucOn)
        MISC->IO_OUTPUT |= (1 << 5);
    else
        MISC->IO_OUTPUT &= ~(1 << 5);
}

void io_set_blue(uint8_t ucOn)
{
    if (ucOn)
        MISC->IO_OUTPUT |= (1 << 4);
    else
        MISC->IO_OUTPUT &= ~(1 << 4);
}

uint8_t io_get_usrbtn()
{
    return (~MISC->IO_INPUT) & 1;
}

uint16_t io_adc_read()
{
    ADC->CTRL |= ADC_CTRL_START_Msk; // start conversion
    // wait for rising edge
    while (!(ADC->STATUS & ADC_STATUS_EOC_Msk))
        ;
    uint16_t adc_value = ADC->OUT;
    ADC->CTRL &= ~ADC_CTRL_START_Msk; // stop conversion

    return adc_value;
}
