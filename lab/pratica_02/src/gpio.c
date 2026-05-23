#include "gpio.h"
#include "soc_AM335x.h"
#include "hw_types.h"

#define MODULEMODEENABLE        0x2   /* VALUE FOR ENABLE GPIO                  */
#define IDLEST                  0x3   /* VALUE FOR VERIFY IDLEST FOR GPIO CLOCK */
#define CM_PER_GPIO_1_CLKCTRL   0xAC  /* OFFSET FOR CLOCK GPIO1                 */
#define CM_PER_GPIO_2_CLKCTRL   0xB0  /* OFFSET FOR CLOCK GPIO2                 */
#define CM_PER_GPIO_3_CLKCTRL   0xB4  /* OFFSET FOR CLOCK GPIO3                 */
#define MODE_7_IO               0x7   /* MODE 7 IS GPIO ON PIN                  */
#define GPIO_OE                 0x134 /* OFFSET FOR OE GPIOx                    */

// =============================================================================
//                      PRIVATE FUNCTIONS PROTOTYPES
// =============================================================================

void enableClockGPIOx(volatile unsigned int gpio_number);
void setPinMuxGPIO(volatile unsigned int pinName);
void setOEDirection(volatile unsigned int gpio_number , volatile unsigned int reg_gpio, volatile unsigned int direction);
void verifyStatusClockGPIOx(volatile unsigned int gpio_number);

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
    case 3:
        if(direction){
            HWREG(SOC_GPIO_3_REGS + GPIO_OE) |= (1 << reg_gpio);
        } else {
            HWREG(SOC_GPIO_3_REGS + GPIO_OE) &= ~(1 << reg_gpio);
        }
    default:
        break;
    }
}

void verifyStatusClockGPIOx(volatile unsigned int gpio_number)
{
    switch (gpio_number)
    {
    case 1:
        while((HWREG(SOC_CM_PER_REGS + CM_PER_GPIO_1_CLKCTRL) & (IDLEST << 16)) != 0);
        break;
    case 2:
        while((HWREG(SOC_CM_PER_REGS + CM_PER_GPIO_2_CLKCTRL) & (IDLEST << 16)) != 0);
        break;
    case 3:
        while((HWREG(SOC_CM_PER_REGS + CM_PER_GPIO_3_CLKCTRL) & (IDLEST << 16)) != 0);
        break;
    default:
        break;
    }
}

// =============================================================================
