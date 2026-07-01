#ifndef UTILS_H
#define UTILS_H
#include "soc_AM335x.h"
#include "timer.h"
#include "interrupt.h"
#include "gpio.h"
#include "stdbool.h"
#include "uart.h"
#include "stdlib.h"
#define rand (DMTimerCounterGet(SOC_DMTIMER_2_REGS)) 


extern void startSequence(void);

extern void winSequence(void);

extern void loseSequence(void);

extern int buttonCheck(void);

#endif // UTILS_H