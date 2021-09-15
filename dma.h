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

#ifndef __DMA_H
#define __DMA_H

#include <stdint.h>


typedef struct
{
	volatile uint32_t DMA_CTRL;		/* DMA Control Register 0x00 */
	volatile uint32_t DMA_DEST_ADDR;	/* DMA Destination Address 0x04 */
	volatile uint32_t DMA_XFER_CNT;	/* DMA Transfer Count 0x08 */
	volatile uint32_t CFG_FLASH_HEADER;	/* CFG FLASH Header 0x0C */
	volatile uint32_t DMA_INTR;		/* DMA Interrupt Register 0x10 */
	volatile uint32_t DMA_INTR_MASK;	/* DMA Interrupt Mask Register 0x14 */
} DMA_typedef;


#define DMA_BASE (0x40007400)
#define DMA ((DMA_typedef*) DMA_BASE)

#define	DMA_CTRL_START_BIT		 ((uint32_t) (0x00000001))
#define DMA_CTRL_STOP_BIT		 ((uint32_t) (0x00000002))
#define DMA_CTRL_AHB_SEL_BIT		 ((uint32_t) (0x00000004))



#endif