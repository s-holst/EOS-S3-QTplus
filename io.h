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

#ifndef __IO_H
#define __IO_H

#include <stdint.h>

void io_init();
void io_set_red(uint8_t ucOn);
void io_set_green(uint8_t ucOn);
void io_set_blue(uint8_t ucOn);
uint8_t io_get_usrbtn();
uint16_t io_adc_read();

#endif