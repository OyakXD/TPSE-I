#include "soc_AM335x.h"
#include "hw_types.h"
#include "system.h"
#include "gpio.h"
#include <stdbool.h>

/* OFFSETS IN  USAGE */
#define CONF_GPMC_CLK           0x88C
#define CONF_GPMC_A5            0x854
#define CONF_GPMC_AD12          0x830
#define CONF_GPMC_AD15          0x83C
#define GPIO_SETDATAOUT         0x194
#define GPIO_CLEARDATAOUT       0x190
#define GPIO_DATAIN             0x138
#define GPIO_DATAOUT            0x13C
/* ------------------------------------*/

int main(){

    systemInit();
    
    /* config CLOCKS*/
    enableClockGPIOx(1);
    enableClockGPIOx(2);
    /*-----------------*/

    /* set pinmux */
    setPinMuxGPIO(CONF_GPMC_A5);
    setPinMuxGPIO(CONF_GPMC_AD15);
    //setPinMuxGPIO(CONF_GPMC_CLK);
    HWREG(SOC_CONTROL_REGS + CONF_GPMC_CLK) |= 0x37;
    //setPinMuxGPIO(CONF_GPMC_AD12);
    HWREG(SOC_CONTROL_REGS + CONF_GPMC_AD12) |= 0x37;
    /*---------------------------*/

    /* set direction*/
    setOEDirection(1,15,0);
    setOEDirection(1,21,0);
    setOEDirection(1,22,0);
    setOEDirection(1,23,0);
    setOEDirection(1,24,0);
    setOEDirection(2,1,1);
    setOEDirection(1,12,1);
    /*----------------------*/

    while(1){
        if(!(HWREG(SOC_GPIO_1_REGS + GPIO_DATAIN) & (1 << 12))){
            if(!(HWREG(SOC_GPIO_2_REGS + GPIO_DATAIN) & (1 << 1))){
                HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << 24);
                for(volatile unsigned int ra = 0; ra < 50000000; ra++);
                HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << 24);
                for(volatile unsigned int ra = 0; ra < 50000000; ra++);
                HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << 23);
                for(volatile unsigned int ra = 0; ra < 50000000; ra++);
                HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << 23);
                HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << 22);
                for(volatile unsigned int ra = 0; ra < 50000000; ra++);
                HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << 22);
                HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << 21);
                for(volatile unsigned int ra = 0; ra < 50000000; ra++);
                HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << 21);
                for(volatile unsigned int ra = 0; ra < 50000000; ra++);
                HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << 15);
                for(volatile unsigned int ra = 0; ra < 50000000; ra++);
                HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << 15);
            }
            HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << 24);
            for(volatile unsigned int ra = 0; ra < 50000000; ra++);
            HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << 24);
            for(volatile unsigned int ra = 0; ra < 50000000; ra++);
            HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << 23);
            for(volatile unsigned int ra = 0; ra < 50000000; ra++);
            HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << 23);
            HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << 22);
            for(volatile unsigned int ra = 0; ra < 50000000; ra++);
            HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << 22);
            HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << 21);
            for(volatile unsigned int ra = 0; ra < 50000000; ra++);
            HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << 21);
        } else {
            HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << 21);
            for(volatile unsigned int ra = 0; ra < 5000000; ra++);
            HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << 21);
            for(volatile unsigned int ra = 0; ra < 5000000; ra++);
            HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << 22);
            for(volatile unsigned int ra = 0; ra < 5000000; ra++);
            HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << 22);
            HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << 23);
            for(volatile unsigned int ra = 0; ra < 5000000; ra++);
            HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << 23);
            HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << 24);
            for(volatile unsigned int ra = 0; ra < 5000000; ra++);
            HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << 24);
        }
     
    }
    

    /* TESTES COM BOTAO
    while(1){
        if(!(HWREG(SOC_GPIO_1_REGS + GPIO_DATAIN) & (1 << 12))){
            HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << 21);
        } else if(!(HWREG(SOC_GPIO_2_REGS + GPIO_DATAIN) & (1 << 1))) {
            HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << 22);
        } else {
            HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << 21);
            HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << 22);
        }
        
    }
    */
}