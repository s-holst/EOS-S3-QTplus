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

#include "regs/aip.h"
#include "regs/cru.h"
#include "regs/iomux.h"
#include "regs/misc.h"
#include "regs/adc.h"

#include "uart.h"
#include "i2c.h"

int main(void)
{
    // Set main clock to 72 MHz
    AIP->OSC_CTRL_1 = 2194;
    CRU->CLK_CTRL_A_0 = 0;

    uart_init(); // enables printf
    i2c_init();

    IOMUX->PAD[6] = IOMUX_PAD_6_FSEL_GPIO0 | IOMUX_PAD_OEN_DISABLE | IOMUX_PAD_REN_ENABLE; // USR button
    IOMUX->PAD[18] = IOMUX_PAD_18_FSEL_GPIO4 | IOMUX_PAD_E_4MA;                            // Route GPIO4 -> Blue LED on Pad 18
    IOMUX->PAD[21] = IOMUX_PAD_21_FSEL_GPIO5 | IOMUX_PAD_E_4MA;                            // Route GPIO5 -> Green LED on Pad 21
    IOMUX->PAD[22] = IOMUX_PAD_22_FSEL_GPIO6 | IOMUX_PAD_E_4MA;                            // Route GPIO6 -> Red LED on Pad 22

    // Output high on Pad 26 for battery voltage monitoring
    IOMUX->PAD[26] = IOMUX_PAD_26_FSEL_GPIO1 | IOMUX_PAD_E_4MA;
    MISC->IO_OUTPUT |= (1 << 1);

    // Enable ADC
    CRU->CLK_CTRL_H_0 = CRU_CLK_CTRL_x_0_DIV_BY(72); // C19 = 1MHz
    CRU->CLK_DIVIDER_CLK_GATING |= (1 << 7);
    CRU->C19_CLK_GATE |= 1;
    ADC->CTRL &= ~ADC_CTRL_START_Msk; // stop and conversions

    printf("\n\nInitializing LIS2DH12...\n");
    i2c_write_reg(0x18, 0x23, 0x80);
    i2c_write_reg(0x18, 0x20, 0x57);
    i2c_write_reg(0x18, 0x1f, 0xC0);

    uint32_t counter, adc_value;
    uint8_t b[10];
    uint8_t led_state, led_oldstate;
    uint8_t adc_start = 1;

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
            // read accelerometer
            i2c_read_regs(0x18, 0x80 | 0x28, b, 6);
            int32_t x = ((b[0] >> 6) & 0x3) | ((int32_t)((int8_t)b[1])) << 2;
            int32_t y = ((b[2] >> 6) & 0x3) | ((int32_t)((int8_t)b[3])) << 2;
            int32_t z = ((b[4] >> 6) & 0x3) | ((int32_t)((int8_t)b[5])) << 2;

            // read ADC
            if (adc_start)
            {
                ADC->CTRL |= ADC_CTRL_START_Msk; // start conversion
                while (ADC->STATUS & ADC_STATUS_EOC_Msk)
                    ;
                adc_start = 0;
            }
            else
            {
                // wait for rising edge
                if (ADC->STATUS & ADC_STATUS_EOC_Msk)
                {
                    adc_value = ADC->OUT;
                    ADC->CTRL &= ~ADC_CTRL_START_Msk; // stop conversion
                    adc_start = 1;
                }
            }
            printf("X %6d Y %6d Z %6d USR %d BAT %d\n", x, y, z, (~MISC->IO_INPUT) & 1, adc_value);
        }
    }

    return 0;
}