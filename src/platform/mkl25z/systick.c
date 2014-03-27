#include <stdint.h>
#include "freedom.h"
#include "common.h"
#include "systick.h"

#define DEBUG_PRINT	

uint32_t cnt_start_value;
uint32_t cnt_end_value;
uint32_t overhead;
volatile uint32_t cnt_tick_value;
    

void systick_init(uint32_t time_in_us)
{
/*
	SYST_CVR = 0x0;	//clear current timer value
    SYST_RVR = 0x00FFFFFF;
    SYST_CSR = SysTick_CSR_CLKSOURCE_MASK | SysTick_CSR_ENABLE_MASK;   
*/
    SYST_RVR = MAIN_FREQ * time_in_us -  1; // 48*10000-1 = 0x752FF
    SYST_CVR = 0x0;	//clear current timer value
    SYST_CSR = SysTick_CSR_CLKSOURCE_MASK | SysTick_CSR_ENABLE_MASK | SysTick_CSR_TICKINT_MASK;
    cnt_tick_value = 0;
}

void systick_disable(void)
{
    SYST_CSR &= ~SysTick_CSR_ENABLE_MASK;
}

void cal_systick_read_overhead(void)
{
  	uint32_t cnt_start_value;
    uint32_t cnt_end_value;
	
	cnt_start_value = SYST_CVR;
  
    cnt_end_value = SYST_CVR;
	
	overhead = cnt_start_value - cnt_end_value;

#ifdef DEBUG_PRINT	
	iprintf("\r\nsystick start value: 0x%x\r\n", cnt_start_value);
	iprintf("systick end value: 0x%x\r\n", cnt_end_value);
	iprintf("systick current value read overhead: 0x%x\r\n", overhead);
#endif

}

/*
    10ms ticker for RTOS or thread in protected runtime like Python/Lua
 */
void SysTick_Handler(void)
{
    cnt_tick_value += 1;
#ifdef DEBUG_PRINT
    iprintf("\r\ntick=0x%x\r\n", cnt_tick_value);
    //iprintf("\r\ntick=0x%x\r\n", SYST_CVR);
#endif    
}