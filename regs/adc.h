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

#ifndef __ADC_H
#define __ADC_H

#include <stdint.h>

#define ADC ((ADC_typedef *)0x40005A00)

typedef struct
{
    volatile uint32_t OUT;    // 0x00 [11:0]R ADC conversion output
    volatile uint32_t STATUS; // 0x04 [0]R 1=end of conversion
    volatile uint32_t CTRL;   // 0x08 [0] 1=start conversion [1] channel <0=ch0> 1=ch1 [2] bat. meas <0=dis> 1=en
} ADC_typedef;

#define ADC_CTRL_START_Msk 0x1
#define ADC_CTRL_CH1_Msk 0x2
#define ADC_CTRL_BAT_MEAS_Msk 0x4

#define ADC_STATUS_EOC_Msk 0x1

#endif