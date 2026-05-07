#include "bbb_regs.h"
#include <stdbool.h>

/* Setup mode, output 0 , input 1*/
#define setupGPIO1(num, key) \
        do { \
            (GPIO1_OE) &= ~((key) << (num)); \
        } while(0)


/* Init clock for gpio1*/
static void initClockGPIO1(){
    CM_PER_GPIO1_CLKCTRL |= 0x2;
}

/* 1° prototipo, tornei ele um pré-processo
static void setupGPIO1(volatile unsigned int num, volatile bool key){
    GPIO1_OE &=  ~(key << num);
}
*/

/* Blink internal leds*/
static void blink_int(volatile unsigned int num){
    GPIO1_SETDATAOUT |= (1 << num);
    for(volatile unsigned int i = 0; i < 100000000; i++);
    GPIO1_CLEARDATAOUT |= (1 << num);
    for(volatile unsigned int i = 0; i < 100000000; i++); 
}

int main(){
    initClockGPIO1();

    setupGPIO1(21, 1);
    setupGPIO1(22, 1);
    setupGPIO1(23, 1);
    setupGPIO1(24, 1);
    
    while(1){

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