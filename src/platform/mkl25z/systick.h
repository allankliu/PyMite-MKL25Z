#ifndef __SYSTICK_H
#define __SYSTICK_H

/* main freq = 48 MHz */
#define MAIN_FREQ   48
/* systick timer interval = 10 ms */
#define TICK_INTVL  10

#define RELOADVAL   MAIN_FREQ/TICK_INTVL - 1

/* Global variables */
extern uint32_t cnt_start_value;
extern uint32_t cnt_end_value;
extern uint32_t overhead;

/* Function declaration */
void systick_init(uint32_t time_in_us);
void systick_disable(void);
void cal_systick_read_overhead(void);

#endif
