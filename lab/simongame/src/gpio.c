#include "gpio.h"
#include "soc_AM335x.h"
#include "hw_types.h"
#include "uart.h"

#define MODULEMODEENABLE        0x2   /* VALUE FOR ENABLE GPIO                  */
#define IDLEST                  0x3   /* VALUE FOR VERIFY IDLEST FOR GPIO CLOCK */
#define CM_PER_GPIO_1_CLKCTRL   0xAC  /* OFFSET FOR CLOCK GPIO1                 */
#define CM_PER_GPIO_2_CLKCTRL   0xB0  /* OFFSET FOR CLOCK GPIO2                 */
#define CM_PER_GPIO_3_CLKCTRL   0xB4  /* OFFSET FOR CLOCK GPIO3                 */
#define MODE_7_IO               0x7   /* MODE 7 IS GPIO ON PIN                  */
#define GPIO_OE                 0x134 /* OFFSET FOR OE GPIOx                    */
#define GPIO_SETDATAOUT         0x194 /* OFFSET FOR SETDATAOUT GPIOx            */
#define GPIO_CLEARDATAOUT       0x190 /* OFFSET FOR CLEARDATAOUT GPIOx          */


typedef struct {
    unsigned int base_addr;
    unsigned int pin_number;
} GPIO_Pin;

/* Botões que vai ser usado para a sequencia*/
GPIO_Pin buttons[4] = 
{
    {SOC_GPIO_1_REGS, 12},
    {SOC_GPIO_1_REGS, 16},
    {SOC_GPIO_1_REGS, 17},
    {SOC_GPIO_1_REGS, 28}
};

/* Leds que vai ser usado para a sequencia */
GPIO_Pin leds[4] = 
{
    {SOC_GPIO_2_REGS,1},
    {SOC_GPIO_2_REGS,2},
    {SOC_GPIO_2_REGS,3},
    {SOC_GPIO_2_REGS,4}
};

// =============================================================================
//                      PRIVATE FUNCTIONS PROTOTYPES
// =============================================================================

void enableClockGPIOx(volatile unsigned int gpio_number);
void setPinMuxGPIO(volatile unsigned int pinName);
void setOEDirection(volatile unsigned int gpio_number , volatile unsigned int reg_gpio, volatile unsigned int direction);
void verifyStatusClockGPIOx(volatile unsigned int gpio_number);
void setupLeds(void);
void allLedOff(void);
void flashLED(int ledNumber);

// =============================================================================


// =============================================================================
//                      PUBLIC FUNCTIONS IMPLEMENTATIONS
// =============================================================================

void enableClockGPIOx(volatile unsigned int gpio_number)
{
    switch (gpio_number)
    {
    case 1:
        HWREG(SOC_CM_PER_REGS + CM_PER_GPIO_1_CLKCTRL) |= MODULEMODEENABLE;
        while((HWREG(SOC_CM_PER_REGS + CM_PER_GPIO_1_CLKCTRL) & (IDLEST << 16)) != 0);
        break;
    case 2:
        HWREG(SOC_CM_PER_REGS + CM_PER_GPIO_2_CLKCTRL) |= MODULEMODEENABLE; 
        break;
    case 3:
        HWREG(SOC_CM_PER_REGS + CM_PER_GPIO_3_CLKCTRL) |= MODULEMODEENABLE;
    default:
        break;
    }
}

void setPinMuxGPIO(volatile unsigned int pinName)
{
    HWREG(SOC_CONTROL_REGS + pinName) |= MODE_7_IO;
}

void setOEDirection(volatile unsigned int gpio_number, volatile unsigned int reg_gpio ,volatile unsigned int direction)
{
    switch (gpio_number)
    {
    case 1:
        // 0h The corresponding GPIO port is configured as an output , 1h The corresponding GPIO port is configured as an output
        if(direction){
            HWREG(SOC_GPIO_1_REGS + GPIO_OE) |= (1 << reg_gpio);
        } else {
            HWREG(SOC_GPIO_1_REGS + GPIO_OE) &= ~(1 << reg_gpio);
        }
        break;
    case 2:
        if(direction){
            HWREG(SOC_GPIO_2_REGS + GPIO_OE) |= (1 << reg_gpio);
        } else {
            HWREG(SOC_GPIO_2_REGS + GPIO_OE) &= ~(1 << reg_gpio);
        }
        break;
    case 3:
        if(direction){
            HWREG(SOC_GPIO_3_REGS + GPIO_OE) |= (1 << reg_gpio);
        } else {
            HWREG(SOC_GPIO_3_REGS + GPIO_OE) &= ~(1 << reg_gpio);
        }
        break;
    default:
        break;
    }
}

void setupLeds()
{
    for (int i = 0; i < 4; i++) {
        // leds
        setOEDirection(2, leds[i].pin_number, 0);

        // botões
        setOEDirection(1, buttons[i].pin_number, 1);
    }

    allLedOff();
}

void allLedOff(void)
{
    for (int i = 0; i < 4; i++) 
    {
        HWREG(leds[i].base_addr + GPIO_CLEARDATAOUT) = (1 << leds[i].pin_number);
    }
}

void flashLED(int ledNumber)
{
    HWREG(leds[ledNumber].base_addr + GPIO_SETDATAOUT) = (1 << leds[ledNumber].pin_number);
}





// =============================================================================
