#include "interrupt.h"
#include "hw_types.h"
#include "uart.h"
#include "soc_AM335x.h"

/*offsets in usage*/
#define INTC_SYSCONFIG           0x10
#define INTC_SYSSTATUS           0x14
#define INTC_THRESHOLD           0x68
#define INTC_PRIORITYTHRESHOLD   0xFF
#define INTC_CONTROL             0x48
#define INTC_SIR_IRQ             0x40
#define INTC_MIR_CLEAR3          0xE8
#define INTC_MIR_CLEAR2          0xC8
#define DMTIMER_IRQENABLE_SET    0x2C
#define DMTIMER_IRQSTATUS        0x28
#define GPIO1_IRQSTATUS_SET_0    0x34
#define GPIO1_RISINGDETECT       0x148
#define GPIO1_FALLINGDETECT      0x14C
#define GPIO1_DEBOUNCE           0x150
#define GPIO_IRQSTATUS_0         0x2C
#define INTC_SYSCONFIG_SOFTRESET 0x2
#define INTC_SYSSTATUS_RESETDONE 0x1
#define SYS_INT_GPIOINT1A        98
#define SYS_INT_TINT7            95
volatile bool flag_gpio = true;
volatile bool flag_gpio2 = true;
volatile bool flag_timer = false;

// =============================================================================
//                      PRIVATE FUNCTIONS PROTOTYPES
// =============================================================================
void intAINTCInit(void);
void ISR_Handler(void);
void gpioIsr(void);
void DMTimerIsr(void);
void gpioInterruptInit(void);
void dmTimerInit(void);

// =============================================================================

// =============================================================================
//                      PUBLIC FUNCTIONS IMPLEMENTATIONS
// =============================================================================

void intAINTCInit(void)
{
    /* Reset the ARM interrupt controller */
    HWREG(SOC_AINTC_REGS + INTC_SYSCONFIG) = INTC_SYSCONFIG_SOFTRESET;

    /* Wait for the reset to complete */
    while((HWREG(SOC_AINTC_REGS + INTC_SYSSTATUS) &
            INTC_SYSSTATUS_RESETDONE) != INTC_SYSSTATUS_RESETDONE);
    

    /* Enable any interrupt generation by setting priority threshold */
    HWREG(SOC_AINTC_REGS + INTC_THRESHOLD) = INTC_PRIORITYTHRESHOLD;
}

void dmTimerInit()
{
    /* Interrupt mask */
    HWREG(SOC_AINTC_REGS + INTC_MIR_CLEAR2) = (1 << 31); // 95->bit 31 on register MIR_CLEAR2
}

void gpioInterruptInit()
{
    /* Interrupt mask */
    HWREG(SOC_AINTC_REGS + INTC_MIR_CLEAR3) = (1<<2); //98->bit 2 on register MIR_CLEAR3

    /* Setting interrupt GPIO pin. */
    HWREG(SOC_GPIO_1_REGS + GPIO1_IRQSTATUS_SET_0) |= (1<<28);
    HWREG(SOC_GPIO_1_REGS + GPIO1_IRQSTATUS_SET_0) |= (1<<16);
    /* -----------------------------*/

    /* Enable interrupt generation on detection of a rising edge.*/
    HWREG(SOC_GPIO_1_REGS + GPIO1_FALLINGDETECT) |= (1<<28);
    HWREG(SOC_GPIO_1_REGS + GPIO1_FALLINGDETECT) |= (1<<16);

    /* Enable debounce of detection 
    HWREG(SOC_GPIO_1_REGS + GPIO1_DEBOUNCE) |= (1 << 28);
    HWREG(SOC_GPIO_1_REGS + GPIO1_DEBOUNCE) |= (1 << 16);
    */
}

void ISR_Handler()
{
    unsigned int intrNum;
    
    intrNum = HWREG(SOC_AINTC_REGS + INTC_SIR_IRQ) & 0x7F;
   
    switch (intrNum) 
    {
        case SYS_INT_GPIOINT1A:
            gpioIsr();
            break;
        case SYS_INT_TINT7:
            DMTimerIsr();
            break;
        default:
            break;
    }

    //printS("cheguei", 7);
    /* acknowledge the IRQ */
    HWREG(SOC_AINTC_REGS + INTC_CONTROL) = 0x1;
}

void gpioIsr(void)
{
    unsigned int status = HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_0);

    if (status & (1 << 28)) {
        flag_gpio = false;
        printS("Trocando a sequencia\n\r", 23);
        // limpa flag de interrupção só do bit 28
        HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_0) = (1 << 28);
    }

    if (status & (1 << 16)) {
        flag_gpio2 = false;
        printS("Trocando a frequencia\n\r", 23);
        // limpa flag de interrupção só do bit 28
        HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_0) = (1 << 16);
    }
}

void DMTimerIsr()
{
    flag_timer = true;

    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_IRQSTATUS) = 0x2;
    
}
