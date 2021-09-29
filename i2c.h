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

#ifndef __I2C_H
#define __I2C_H

#include <stdint.h>

int i2c_init();
int i2c_write_byte(uint8_t ucData, uint8_t ucFlags);
int i2c_read_byte(uint8_t *pucData, uint8_t ucFlags);
int i2c_write_regs(uint8_t ucDevAddr, uint8_t ucRegAddr, uint8_t *pucData, uint32_t uiLength);
int i2c_write_reg(uint8_t ucDevAddr, uint8_t ucRegAddr, uint8_t ucData);
int i2c_read_regs(uint8_t ucDevAddr, uint8_t ucRegAddr, uint8_t *pucData, uint32_t uiLength);

int i2c_accel_init();
int i2c_accel_read(int32_t *piX, int32_t *piY, int32_t *piZ);

#endif