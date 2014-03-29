/*
# This file is Copyright 2006, 2007, 2009 Dean Hall.
#
# This file is part of the Python-on-a-Chip program.
# Python-on-a-Chip is free software: you can redistribute it and/or modify
# it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1.
#
# Python-on-a-Chip is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# A copy of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1
# is seen in the file COPYING up one directory from this.
*/


#undef __FILE_ID__
#define __FILE_ID__ 0x70


/** PyMite platform-specific routines for FSL MKL25Z FRDM target */


#include <stdio.h>
#include <stdint.h>
#include "freedom.h"
#include "common.h"
#include "mkl25z4.h"
#include "pm.h"

#define CALLBACK_MS 10

void SysTick_Handler(void)
{
}

PmReturn_t plat_init(void)
{
    uart_init(115200);
    return PM_RET_OK;
}

PmReturn_t plat_deinit(void)
{
    return PM_RET_OK;
}

uint8_t plat_memGetByte(PmMemSpace_t memspace, uint8_t const **paddr)
{
    uint8_t b = 0;
    switch (memspace)
    {
        case MEMSPACE_RAM:
        case MEMSPACE_PROG:
            b = **paddr;
            *paddr += 1;
            return b;
            
        case MEMSPACE_EEPROM:
        case MEMSPACE_SEEPROM:
        case MEMSPACE_OTHER0:
        case MEMSPACE_OTHER1:
        case MEMSPACE_OTHER2:
        case MEMSPACE_OTHER3:
        default:
            return 0;
    }
}

PmReturn_t plat_getByte(uint8_t *b)
{
}

PmReturn_t plat_putByte(uint8_t b)
{
}

PmReturn_t plat_getMsTicks(uint32_t *r_ticks)
{
    *r_ticks = pm_timerMsTicks;
    return PM_RET_OK;
}

void plat_reportError(PmReturn_t result)
{
#ifdef HAVE_DEBUG_INFO
#else
#endif
}
