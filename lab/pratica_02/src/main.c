#include "bbb_regs.h"
#include "hw_types.h"
#include <stdbool.h>

/* Setup mode, output 0 , input 1, reset is 1*/
#define setupGPIO1(num, key) \
        do { \
            (GPIO1_OE) &= ~((key) << (num)); \
        } while(0)

/* o reset do pinmux é o 7, então para este caso declarar o pinmux dele não seria necessário, mas é uma boa prática. */
static void configPINMUX(){
    CONF_GPMC_A5 |= CONF_GPMC_A5_MODE;
}

/* Init clock for gpio1*/
static void initClockGPIO1(){
    CM_PER_GPIO1_CLKCTRL |= CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE;
}


/* Blink internal leds*/
static void blink_int(volatile unsigned int num){
    GPIO1_SETDATAOUT |= (1 << num);
    for(volatile unsigned int i = 0; i < 100000000; i++);
    GPIO1_CLEARDATAOUT |= (1 << num);
    for(volatile unsigned int i = 0; i < 100000000; i++); 
}

int main(){
    initClockGPIO1();
    configPINMUX();

    setupGPIO1(21, 1);
    setupGPIO1(22, 1);
    setupGPIO1(23, 1);
    setupGPIO1(24, 1);
    
    /* Verificação de IDLEST STATUS DO CLOCK DO GPIO1 */
    while(!((CM_PER_GPIO1_CLKCTRL >> 16) & 0x1) && !((CM_PER_GPIO1_CLKCTRL >> 17) & 0x1)){

        blink_int(21);
        blink_int(22);
        blink_int(23);
        blink_int(24);

        blink_int(24);
        blink_int(23);
        blink_int(22);
        blink_int(21);
    }
}