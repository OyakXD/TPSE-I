#include "soc_AM335x.h"
#include "hw_types.h"
#include <stdbool.h>

/* OFFSETS IN  USAGE */
#define CM_PER_GPIO_1_CLKCTRL   0xAC
#define CM_PER_GPIO_2_CLKCTRL   0xB0
#define CONF_GPMC_CSN3          0x888
#define CONF_GPMC_CLK           0x88C
#define CONF_GPMC_A5            0x854
#define MODULEMODEENABLE        0x2
#define CONF_GPMC_A5_MODE       0x7
#define CONF_GPMC_CSN3_MODE     0x7
#define CONF_GPMC_CLK_MODE      0x7
#define GPIO_OE                 0x134
#define GPIO_SETDATAOUT         0x194
#define GPIO_CLEARDATAOUT       0x190
#define WDT_WWPS                0x34
#define WDT_WSPR                0x48
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

    /* Disable WDT */
    HWREG(SOC_WDT_1_REGS + WDT_WSPR) = 0xAAAA;
    while(HWREG(SOC_WDT_1_REGS + WDT_WWPS) & (1 << 4));
    HWREG(SOC_WDT_1_REGS + WDT_WSPR) = 0x5555;
    while(HWREG(SOC_WDT_1_REGS + WDT_WWPS) & (1 << 4));
    
    /* config CLOCKS*/
    HWREG(SOC_CM_PER_REGS + CM_PER_GPIO_1_CLKCTRL) |= MODULEMODEENABLE;
    HWREG(SOC_CM_PER_REGS + CM_PER_GPIO_2_CLKCTRL) |= MODULEMODEENABLE;
    /*-------------------------*/

    /* set pinmux */
    HWREG(SOC_CONTROL_REGS + CONF_GPMC_A5) |= CONF_GPMC_A5_MODE;
    HWREG(SOC_CONTROL_REGS + CONF_GPMC_CLK) |= CONF_GPMC_CLK_MODE;
    /*------------------------------------------*/

    /* set direction*/
    HWREG(SOC_GPIO_1_REGS + GPIO_OE) &= ~(1 << 21);
    HWREG(SOC_GPIO_1_REGS + GPIO_OE) &= ~(1 << 22);
    HWREG(SOC_GPIO_1_REGS + GPIO_OE) &= ~(1 << 23);
    HWREG(SOC_GPIO_1_REGS + GPIO_OE) &= ~(1 << 24);
    HWREG(SOC_GPIO_2_REGS + GPIO_OE) &= ~(1 << 1);
    /*----------------------*/
    
    
    // VERIFICAÇÃO DO STATUS DOS CLOCKS
    while(((HWREG(SOC_CM_PER_REGS + CM_PER_GPIO_1_CLKCTRL >> 16) & 0x3) != 0x3) && ((HWREG(SOC_CM_PER_REGS + CM_PER_GPIO_2_CLKCTRL >> 16) & 0x3) != 0x3)){

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