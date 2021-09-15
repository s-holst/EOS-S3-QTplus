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

#ifndef __PMU_H
#define __PMU_H

#include <stdint.h>

typedef struct
{
	volatile uint32_t MISC_POR_0;               /* 0x000 */
	volatile uint32_t MISC_POR_1;               /* 0x004 */
	volatile uint32_t MISC_POR_2;               /* 0x008 */
	volatile uint32_t MISC_POR_3;               /* 0x00C */
	volatile uint32_t RST_CTRL_0;               /* 0x010 */
	volatile uint32_t RST_CTRL_1;               /* 0x014 */
	volatile uint32_t CHIP_STA_0;               /* 0x018 */
	volatile uint32_t CHIP_STA_1;               /* 0x01C */
	volatile uint32_t WIC_CTRL;                 /* 0x020 */
	volatile uint32_t WIC_STATUS;               /* 0x024 */
	volatile uint32_t reserved[2];
	volatile uint32_t PWR_DWN_SCH;              /* 0x030 */
	volatile uint32_t reserved1[3];
	volatile uint32_t PWR_OFF_OSC;              /* 0x040 */
	volatile uint32_t EXT_WAKING_UP_SRC;        /* 0x044 */
	volatile uint32_t reserved2[10];
	volatile uint32_t SDMA_STATUS;              /* 0x070 */
	volatile uint32_t SDMA_POWER_MODE_CFG;      /* 0x074 */
	volatile uint32_t SDMA_PD_SRC_MASK_N;       /* 0x078 */
	volatile uint32_t SDMA_WU_SRC_MASK_N;       /* 0x07C */
	volatile uint32_t M4_STATUS;                /* 0x080 */
	volatile uint32_t M4_PWR_MODE_CFG;          /* 0x084 */
	volatile uint32_t M4_PD_SRC_MASK_N;         /* 0x088 */
	volatile uint32_t M4_WU_SRC_MASK_N;         /* 0x08C */
	volatile uint32_t FFE_STATUS;               /* 0x090 */
	volatile uint32_t FFE_PWR_MODE_CFG;         /* 0x094 */
	volatile uint32_t FFE_PD_SRC_MASK_N;        /* 0x098 */
	volatile uint32_t FFE_WU_SRC_MASK_N;        /* 0x09C */
	volatile uint32_t FB_STATUS;                // 0x0A0 RHW [0] active, [1] deep sleep, [2] shutdown
	volatile uint32_t FB_PWR_MODE_CFG;          /* 0x0A4 */
	volatile uint32_t FB_PD_SRC_MASK_N;         /* 0x0A8 */
	volatile uint32_t FB_WU_SRC_MASK_N;         /* 0x0AC */
	volatile uint32_t PF_STATUS;                /* 0x0B0 */
	volatile uint32_t PF_PWR_MODE_CFG;          /* 0x0B4 */
	volatile uint32_t PF_PD_SRC_MASK_N;         /* 0x0B8 */
	volatile uint32_t PF_WU_SRC_MASK_N;         /* 0x0BC */
	volatile uint32_t M4S0_SRAM_STATUS;         /* 0x0C0 */
	volatile uint32_t M4S0_PWR_MODE_CFG;        /* 0x0C4 */
	volatile uint32_t M4S0_PD_SRC_MASK_N;       /* 0x0C8 */
	volatile uint32_t M4S0_WU_SRC_MASK_N;       /* 0x0CC */
	volatile uint32_t A1_STATUS; 		        /* 0x0D0 */
	volatile uint32_t A1_PWR_MODE_CFG;          // 0x0D4 [1:0] 1=retention 2=shutdown
	volatile uint32_t A1_PD_SRC_MASK_N;         /* 0x0D8 */
	volatile uint32_t A1_WU_SRC_MASK_N;         /* 0x0DC */
	volatile uint32_t MISC_STATUS;              // 0x0E0 RHW [4] 1=I2S_power_on
	volatile uint32_t AUDIO_STATUS;             /* 0x0E4 */
	volatile uint32_t M4_SRAM_STATUS;            /* 0x0E8 */
	volatile uint32_t AUDIO_WU_SRC_MASK_N;      /* 0x0EC */
	volatile uint32_t reserved3[4];
	volatile uint32_t M4_MEM_CTRL_0;            /* 0x100 */
	volatile uint32_t M4_MEM_CTRL_1;            /* 0x104 */
	volatile uint32_t PF_MEM_CTRL_0;            /* 0x108 */
	volatile uint32_t PF_MEM_CTRL_1;            /* 0x10C */
	volatile uint32_t FFE_MEM_CTRL_0;           /* 0x110 */
	volatile uint32_t FFE_MEM_CTRL_1;           /* 0x114 */
	volatile uint32_t AUDIO_MEM_CTRL_0;         /* 0x118 */
	volatile uint32_t AUDIO_MEM_CTRL_1;			/* 0x11C */
	volatile uint32_t M4_MEM_CFG;				/* 0x120 */
	volatile uint32_t PF_MEM_CFG;				/* 0x124 */
	volatile uint32_t FFE_MEM_CFG;				/* 0x128 */
	volatile uint32_t AUDIO_MEM_CFG;			/* 0x12C */
	volatile uint32_t M4_MEM_CTRL_PWR_0;	/* 0x130 */
	volatile uint32_t M4_MEM_CTRL_PWR_1;	/* 0x134 */
	volatile uint32_t M4_MEM_CTRL_PWR_2;	/* 0x138 */
	volatile uint32_t reserved4[1];
	volatile uint32_t SDMA_MEM_CTRL_0;		/* 0x140 */
	volatile uint32_t SDMA_MEM_CTRL_1;		/* 0x144 */
	volatile uint32_t reserved5[14];
	volatile uint32_t MEM_PWR_DOWN_CTRL;	/* 0x180 */
	volatile uint32_t PMU_TIMER_CFG_0;		/* 0x184 */
	volatile uint32_t PMU_TIMER_CFG_1;		/* 0x188 */
	volatile uint32_t PDWU_TIMER_CFG;		/* 0x18C */
	volatile uint32_t reserved6[28];
	volatile uint32_t FFE_FB_PF_SW_PD;		/* 0x200 */
	volatile uint32_t M4_SRAM_SW_PD;		/* 0x204 */
	volatile uint32_t MISC_SW_PD;               /* 0x208 */
	volatile uint32_t AUDIO_SW_PD;              /* 0x20C */
	volatile uint32_t FFE_FB_PF_SW_WU;          /* 0x210 */
	volatile uint32_t M4_SRAM_SW_WU;             /* 0x214 */
	volatile uint32_t MISC_SW_WU;               /* 0x218 */
	volatile uint32_t AUD_SRAM_SW_WU;		/* 0x21C */
	volatile uint32_t PMU_STM_PRIORITY;         /* 0x220 */
	volatile uint32_t reserved7[3];
	volatile uint32_t M4SRAM_SSW_LPMF;			/* 0x230 */
	volatile uint32_t M4SRAM_SSW_LPMH_MASK_N;	/* 0x234 */
	volatile uint32_t reserved8[106];
	volatile uint32_t EFUSE_BITS;    	      /* 0x3E0 */
	volatile uint32_t reserved9[1];
	volatile uint32_t FBVLPMinWidth;          /* 0x3E8 */
	volatile uint32_t APRebootStatus;          /* 0x3EC */
	volatile uint32_t GEN_PURPOSE_0;            /* 0x3F0 */
	volatile uint32_t FB_ISOLATION;            /* 0x3F4 */
	volatile uint32_t GEN_PURPOSE_1;			/* 0x3F8 */

} PMU_typedef;

#define PMU_BASE (0x40004400)
#define PMU ((PMU_typedef *) PMU_BASE)

#define PMU_FFE_FB_PF_SW_WU_PF_WU_Msk  ((uint32_t) (0x00000004))
#define PMU_FFE_FB_PF_SW_WU_FB_WU_Msk  ((uint32_t) (0x00000002))
#define PMU_FFE_FB_PF_SW_WU_FFE_WU_Msk ((uint32_t) (0x00000001))


#endif