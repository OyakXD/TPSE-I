#include "soc_AM335x.h"
#include "hw_types.h"
#include "system.h"
#include "gpio.h"
#include "uart.h"
#include "timer.h"
#include <stdbool.h>

/* OFFSETS IN  USAGE */
#define GPIO_SETDATAOUT                0x194
#define GPIO_CLEARDATAOUT              0x190
/* ------------------------------------*/
                               
static void blink(volatile unsigned int num){

    HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << num);
    DelayMS(1); 
    HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << num);
    DelayMS(1);   
}

int main(){

    systemInit();
    
    while(1){
        blink(12);
    }
}