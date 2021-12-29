#ifndef _NVIC_H
#define _NVIC_H

#include "typedef.h"

#define NVIC_ICTR	*(volatile uint32_t *) 0xE000E004
#define NVIC_SCSR       *(volatile uint32_t *) 0xE000E010
#define NVIC_SRVR       *(volatile uint32_t *) 0xE000E014
#define NVIC_SCVR       *(volatile uint32_t *) 0xE000E018
#define NVIC_SCALIB     *(volatile uint32_t *) 0xE000E01C

#define NVIC_ISER0       *(volatile uint32_t *) 0xE000E100
#define NVIC_ISER1       *(volatile uint32_t *) 0xE000E104
#define NVIC_ISER2       *(volatile uint32_t *) 0xE000E108
#define NVIC_ISER3       *(volatile uint32_t *) 0xE000E10C
#define NVIC_ISER4       *(volatile uint32_t *) 0xE000E110
#define NVIC_ISER5       *(volatile uint32_t *) 0xE000E114
#define NVIC_ISER6       *(volatile uint32_t *) 0xE000E118
#define NVIC_ISER7       *(volatile uint32_t *) 0xE000E11C

#define NVIC_ICER0       *(volatile uint32_t *) 0xE000E180
#define NVIC_ICER1       *(volatile uint32_t *) 0xE000E184
#define NVIC_ICER2       *(volatile uint32_t *) 0xE000E188
#define NVIC_ICER3       *(volatile uint32_t *) 0xE000E18C
#define NVIC_ICER4       *(volatile uint32_t *) 0xE000E190
#define NVIC_ICER5       *(volatile uint32_t *) 0xE000E194
#define NVIC_ICER6       *(volatile uint32_t *) 0xE000E198
#define NVIC_ICER7       *(volatile uint32_t *) 0xE000E19C

#define NVIC_ISPR0       *(volatile uint32_t *) 0xE000E200
#define NVIC_ISPR1       *(volatile uint32_t *) 0xE000E204
#define NVIC_ISPR2       *(volatile uint32_t *) 0xE000E208
#define NVIC_ISPR3       *(volatile uint32_t *) 0xE000E20C
#define NVIC_ISPR4       *(volatile uint32_t *) 0xE000E210
#define NVIC_ISPR5       *(volatile uint32_t *) 0xE000E214
#define NVIC_ISPR6       *(volatile uint32_t *) 0xE000E218
#define NVIC_ISPR7       *(volatile uint32_t *) 0xE000E21C

#define NVIC_ICPR0       *(volatile uint32_t *) 0xE000E280
#define NVIC_ICPR1       *(volatile uint32_t *) 0xE000E284
#define NVIC_ICPR2       *(volatile uint32_t *) 0xE000E288
#define NVIC_ICPR3       *(volatile uint32_t *) 0xE000E28C
#define NVIC_ICPR4       *(volatile uint32_t *) 0xE000E290
#define NVIC_ICPR5       *(volatile uint32_t *) 0xE000E294
#define NVIC_ICPR6       *(volatile uint32_t *) 0xE000E298
#define NVIC_ICPR7       *(volatile uint32_t *) 0xE000E29C

#define NVIC_IABR0       *(volatile uint32_t *) 0xE000E300
#define NVIC_IABR1       *(volatile uint32_t *) 0xE000E304
#define NVIC_IABR2       *(volatile uint32_t *) 0xE000E308
#define NVIC_IABR3       *(volatile uint32_t *) 0xE000E30C
#define NVIC_IABR4       *(volatile uint32_t *) 0xE000E310
#define NVIC_IABR5       *(volatile uint32_t *) 0xE000E314
#define NVIC_IABR6       *(volatile uint32_t *) 0xE000E318
#define NVIC_IABR7       *(volatile uint32_t *) 0xE000E31C

#define NVIC_IPR0       *(volatile uint32_t *) 0xE000E400
#define NVIC_IPR1       *(volatile uint32_t *) 0xE000E404
#define NVIC_IPR2       *(volatile uint32_t *) 0xE000E408
#define NVIC_IPR3       *(volatile uint32_t *) 0xE000E40C
#define NVIC_IPR4       *(volatile uint32_t *) 0xE000E410
#define NVIC_IPR5       *(volatile uint32_t *) 0xE000E414
#define NVIC_IPR6       *(volatile uint32_t *) 0xE000E418
#define NVIC_IPR7       *(volatile uint32_t *) 0xE000E41C
#define NVIC_IPR8       *(volatile uint32_t *) 0xE000E420
#define NVIC_IPR9       *(volatile uint32_t *) 0xE000E424
#define NVIC_IPR10       *(volatile uint32_t *) 0xE000E428
#define NVIC_IPR11       *(volatile uint32_t *) 0xE000E42C
#define NVIC_IPR12       *(volatile uint32_t *) 0xE000E430
#define NVIC_IPR13       *(volatile uint32_t *) 0xE000E434
#define NVIC_IPR14       *(volatile uint32_t *) 0xE000E438
#define NVIC_IPR15       *(volatile uint32_t *) 0xE000E43C
#define NVIC_IPR16       *(volatile uint32_t *) 0xE000E440
#define NVIC_IPR17       *(volatile uint32_t *) 0xE000E444
#define NVIC_IPR18       *(volatile uint32_t *) 0xE000E448
#define NVIC_IPR19       *(volatile uint32_t *) 0xE000E44C
#define NVIC_IPR20       *(volatile uint32_t *) 0xE000E450
#define NVIC_IPR21       *(volatile uint32_t *) 0xE000E454
#define NVIC_IPR22       *(volatile uint32_t *) 0xE000E458
#define NVIC_IPR23       *(volatile uint32_t *) 0xE000E45C
#define NVIC_IPR24       *(volatile uint32_t *) 0xE000E460
#define NVIC_IPR25       *(volatile uint32_t *) 0xE000E464
#define NVIC_IPR26       *(volatile uint32_t *) 0xE000E468
#define NVIC_IPR27       *(volatile uint32_t *) 0xE000E46C
#define NVIC_IPR28       *(volatile uint32_t *) 0xE000E470
#define NVIC_IPR29       *(volatile uint32_t *) 0xE000E474
#define NVIC_IPR30       *(volatile uint32_t *) 0xE000E478
#define NVIC_IPR31       *(volatile uint32_t *) 0xE000E47C
#define NVIC_IPR32       *(volatile uint32_t *) 0xE000E480
#define NVIC_IPR33       *(volatile uint32_t *) 0xE000E484
#define NVIC_IPR34       *(volatile uint32_t *) 0xE000E488
#define NVIC_IPR35       *(volatile uint32_t *) 0xE000E48C
#define NVIC_IPR36       *(volatile uint32_t *) 0xE000E490
#define NVIC_IPR37       *(volatile uint32_t *) 0xE000E494
#define NVIC_IPR38       *(volatile uint32_t *) 0xE000E498
#define NVIC_IPR39       *(volatile uint32_t *) 0xE000E49C
#define NVIC_IPR40       *(volatile uint32_t *) 0xE000E4A0
#define NVIC_IPR41       *(volatile uint32_t *) 0xE000E4A4
#define NVIC_IPR42       *(volatile uint32_t *) 0xE000E4A8
#define NVIC_IPR43       *(volatile uint32_t *) 0xE000E4AC
#define NVIC_IPR44       *(volatile uint32_t *) 0xE000E4B0
#define NVIC_IPR45       *(volatile uint32_t *) 0xE000E4B4
#define NVIC_IPR46       *(volatile uint32_t *) 0xE000E4B8
#define NVIC_IPR47       *(volatile uint32_t *) 0xE000E4BC
#define NVIC_IPR48       *(volatile uint32_t *) 0xE000E4C0
#define NVIC_IPR49       *(volatile uint32_t *) 0xE000E4C4
#define NVIC_IPR50       *(volatile uint32_t *) 0xE000E4C8
#define NVIC_IPR51       *(volatile uint32_t *) 0xE000E4CC
#define NVIC_IPR52       *(volatile uint32_t *) 0xE000E4D0
#define NVIC_IPR53       *(volatile uint32_t *) 0xE000E4D4
#define NVIC_IPR54       *(volatile uint32_t *) 0xE000E4D8
#define NVIC_IPR55       *(volatile uint32_t *) 0xE000E4DC
#define NVIC_IPR56       *(volatile uint32_t *) 0xE000E4E0
#define NVIC_IPR57       *(volatile uint32_t *) 0xE000E4E4
#define NVIC_IPR58       *(volatile uint32_t *) 0xE000E4E8
#define NVIC_IPR59       *(volatile uint32_t *) 0xE000E4EC
#define NVIC_IPR60       *(volatile uint32_t *) 0xE000E4F0
#define NVIC_IPR61       *(volatile uint32_t *) 0xE000E4F4
#define NVIC_IPR62       *(volatile uint32_t *) 0xE000E4F8
#define NVIC_IPR63       *(volatile uint32_t *) 0xE000E4FC

#define NVIC_CPUIDBR            *(volatile uint32_t *) 0xE000ED00
#define NVIC_ICSR       *(volatile uint32_t *) 0XE000ED04
#define NVIC_VTOR       *(volatile uint32_t *) 0xE000ED08
#define NVIC_AIRCR      *(volatile uint32_t *) 0xE000ED0C
#define NVIC_SCR        *(volatile uint32_t *) 0xE000ED10
#define NVIC_CCR        *(volatile uint32_t *) 0xE000ED14
#define NVIC_SHPR0      *(volatile uint32_t *) 0xE000ED18
#define NVIC_SHPR1      *(volatile uint32_t *) 0xE000ED1C
#define NVIC_SHPR2      *(volatile uint32_t *) 0xE000ED20
#define NVIC_SHCSR      *(volatile uint32_t *) 0xE000ED24
#define NVIC_CFSR       *(volatile uint32_t *) 0xE000ED28
#define NVIC_HFSR       *(volatile uint32_t *) 0xE000ED2C
#define NVIC_DFSR       *(volatile uint32_t *) 0xE000ED30
#define NVIC_MMAR       *(volatile uint32_t *) 0xE000ED34
#define NVIC_BFAR       *(volatile uint32_t *) 0xE000ED38
#define NVIC_AFSR       *(volatile uint32_t *) 0xE000ED3C

#define NVIC_PFR0       *(volatile uint32_t *) 0xE000ED40
#define NVIC_PFR1       *(volatile uint32_t *) 0xE000ED44

#define NVIC_DFR0       *(volatile uint32_t *) 0xE000ED48

#define NVIC_AFR0       *(volatile uint32_t *) 0xE000ED4C

#define NVIC_MMFR0       *(volatile uint32_t *) 0xE000ED50
#define NVIC_MMFR1       *(volatile uint32_t *) 0xE000ED54
#define NVIC_MMFR2       *(volatile uint32_t *) 0xE000ED58
#define NVIC_MMFR3       *(volatile uint32_t *) 0xE000ED5C

#define NVIC_ISAR0       *(volatile uint32_t *) 0xE000ED60
#define NVIC_ISAR1       *(volatile uint32_t *) 0xE000ED64
#define NVIC_ISAR2       *(volatile uint32_t *) 0xE000ED68
#define NVIC_ISAR3       *(volatile uint32_t *) 0xE000ED6C
#define NVIC_ISAR4       *(volatile uint32_t *) 0xE000ED70

#define NVIC_STIR       *(volatile uint32_t *) 0xE000EF00

#define NVIC_PID4       *(volatile uint32_t *) 0xE000EFD0
#define NVIC_PID5       *(volatile uint32_t *) 0xE000EFD4
#define NVIC_PID6       *(volatile uint32_t *) 0xE000EFD8
#define NVIC_PID7       *(volatile uint32_t *) 0xE000EFDC
#define NVIC_PID0       *(volatile uint32_t *) 0xE000EFE0
#define NVIC_PID1       *(volatile uint32_t *) 0xE000EFE4
#define NVIC_PID2       *(volatile uint32_t *) 0xE000EFE8
#define NVIC_PID3       *(volatile uint32_t *) 0xE000EFEC

#define NVIC_CID0       *(volatile uint32_t *) 0xE000EFF0
#define NVIC_CID1       *(volatile uint32_t *) 0xE000EFF4
#define NVIC_CID2       *(volatile uint32_t *) 0xE000EFF8
#define NVIC_CID3       *(volatile uint32_t *) 0xE000EFFC

#endif
