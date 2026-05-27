#include "soc_AM335x.h"
#include "hw_types.h"
#include "system.h"
#include "gpio.h"
#include <stdbool.h>

/* OFFSETS IN  USAGE */
#define CONF_GPMC_CLK           0x88C
#define CONF_GPMC_A5            0x854
#define GPIO_SETDATAOUT         0x194
#define GPIO_CLEARDATAOUT       0x190           
/* ------------------------------------*/

/* Blink internal leds*/
static void blink(volatile unsigned int num){
    HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) |= (1 << num);
    HWREG(SOC_GPIO_2_REGS + GPIO_SETDATAOUT) |= (1 << num);
    for(volatile unsigned int i = 0; i < 100000000; i++);
    HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) |= (1 << num);
    HWREG(SOC_GPIO_2_REGS + GPIO_CLEARDATAOUT) |= (1 << num);
    for(volatile unsigned int i = 0; i < 100000000; i++); 
}


int main(){

    systemInit();
    
    /* config CLOCKS*/
    enableClockGPIOx(1);
    enableClockGPIOx(2);
    /*-----------------*/

    /* set pinmux */
    setPinMuxGPIO(CONF_GPMC_A5);
    setPinMuxGPIO(CONF_GPMC_CLK);
    /*------------------------------------------*/

    /* set direction*/
    setOEDirection(1,21,0);
    setOEDirection(1,22,0);
    setOEDirection(1,23,0);
    setOEDirection(1,24,0);
    setOEDirection(2,1,0);
    /*----------------------*/
    
    while(1){

        blink(21);
        blink(22);
        blink(23);
        blink(24);

        blink(1);
        blink(24);
        blink(23);
        blink(22);
        blink(21);
    
    }
}