#include "hw_types.h"
#include "soc_AM335x.h"
#include "timer.h"
#include "uart.h"

#define MODULEMODEENABLE               0x2 /*VALUE ENABLE CLOCK*/
#define CM_PER_TIMER7_CLKCTRL          0x7C
#define CM_PER_TIMER2_CLKCTRL          0x80
#define CM_PER_TIMER3_CLKCTRL          0x84
#define CM_PER_TIMER4_CLKCTRL          0x88
#define CM_PER_TIMER5_CLKCTRL          0xEC
#define CM_PER_TIMER6_CLKCTRL          0xF0
#define DMTIMER_TSICR                  0x54     
#define DMTIMER_TSICR_POSTED           0x4
#define DMTIMER_TWPS                   0x48
#define DMTIMER_TPWS_W_PEND_TCLR       0x1
#define DMTIMER_TPWS_W_PEND_TCRR       0x2
#define DMTIMER_TCLR                   0x38
#define DMTIMER_TCLR_ST                0x1
#define DMTIMER_TCRR                   0x3C
#define DMTIMER_TLDR                   0x40
#define DMTIMER_WRITE_POST_TCRR        (1 << 1)
#define DMTIMER_WRITE_POST_TCLR        (1 << 0)
#define TIMER_1S_COUNT                 24000000
#define TIMER_1MS_COUNT                24000
#define TIMER_OVERFLOW                 0xFFFFFFFF
#define DMTIMER_IRQENABLE_SET          0x2C
#define DMTIMER_IRQENABLE_CLR          0x30
extern volatile bool flag_timer;

/*
In this mode, it is mandatory that the CPU checks the status bit prior to any write access. In case a write is
attempted to a register with a previous access pending, the previous access is discarded without notice
(this can lead to unexpected results also).

Neste modo, é obrigatório que a CPU verifique o bit de status antes de qualquer acesso de escrita. Caso uma escrita seja
tentada em um registrador com um acesso anterior pendente, o acesso anterior é descartado sem aviso prévio
(isso também pode levar a resultados inesperados).

PAG DATASHEET - 4449
*/
#define DMTimerWaitForWrite(reg, baseAdd) \
                                if (HWREG(baseAdd + DMTIMER_TSICR) & DMTIMER_TSICR_POSTED) \
                                while((reg & DMTimerWritePostedStatusGet(baseAdd)));

// =============================================================================
//                      PRIVATE FUNCTIONS PROTOTYPES
// =============================================================================

void timerInit(void);
void enableClockDMTIMERx(volatile unsigned int numDMTIMER);
unsigned int DMTimerWritePostedStatusGet(unsigned int baseAdd);
void DMTimerCounterSet(unsigned int baseAdd, unsigned int counter);
unsigned int DMTimerCounterGet(unsigned int baseAdd);
void DMTimerEnable(unsigned int baseAdd);
void DMTimerDisable(unsigned int baseAdd);
void Delay(unsigned int us);
void DelayMS(unsigned int us);
void DelayMSINT(unsigned int ms);
void DelaySINT(unsigned int s);

// =============================================================================

// =============================================================================
//                      PUBLIC FUNCTIONS IMPLEMENTATIONS
// =============================================================================

void timerInit()
{
    /* Configures the interface to posted mode for better write latency
       bit 2 (posted) enable posted mode*/
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TSICR) |= DMTIMER_TSICR_POSTED;

    // Ensures the timer is stopped before configuration
    while(HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TWPS) & DMTIMER_TPWS_W_PEND_TCLR); // waits for past synchronizations

    HWREG(SOC_DMTIMER_7_REGS+DMTIMER_TCLR) &= ~DMTIMER_TCLR_ST; // disable timer

    // Resets the counter and load register
    while(HWREG(SOC_DMTIMER_7_REGS+DMTIMER_TWPS) & DMTIMER_TPWS_W_PEND_TCRR); // waits for past synchronizations

    /* reset counter and load register */
    HWREG(SOC_DMTIMER_7_REGS+DMTIMER_TCRR) = 0x00000000;
    HWREG(SOC_DMTIMER_7_REGS+DMTIMER_TLDR) = 0x00000000;
}

void enableClockDMTIMERx(volatile unsigned int numDMTIMER) 
{
    switch (numDMTIMER)
    {
    case 2:
        HWREG(SOC_CM_PER_REGS + CM_PER_TIMER2_CLKCTRL) = MODULEMODEENABLE;
        break;
    case 3:
        HWREG(SOC_CM_PER_REGS + CM_PER_TIMER3_CLKCTRL) = MODULEMODEENABLE;
        break;
    case 4:
        HWREG(SOC_CM_PER_REGS + CM_PER_TIMER4_CLKCTRL) = MODULEMODEENABLE;
        break;
    case 5:
        HWREG(SOC_CM_PER_REGS + CM_PER_TIMER5_CLKCTRL) = MODULEMODEENABLE;
        break;
    case 6:
        HWREG(SOC_CM_PER_REGS + CM_PER_TIMER6_CLKCTRL) = MODULEMODEENABLE;
        break;
    case 7:
        HWREG(SOC_CM_PER_REGS + CM_PER_TIMER7_CLKCTRL) = MODULEMODEENABLE;
        break;
    default:
        break;
    }
}

unsigned int DMTimerWritePostedStatusGet(unsigned int baseAdd)
{
    return (HWREG(baseAdd + DMTIMER_TWPS));
}

void DMTimerCounterSet(unsigned int baseAdd, unsigned int counter)
{
    DMTimerWaitForWrite(DMTIMER_WRITE_POST_TCRR, baseAdd);

    HWREG(baseAdd + DMTIMER_TCRR) = counter;
}

unsigned int DMTimerCounterGet(unsigned int baseAdd)
{
    DMTimerWaitForWrite(DMTIMER_WRITE_POST_TCRR, baseAdd);

    return (HWREG(baseAdd + DMTIMER_TCRR));
}

void DMTimerEnable(unsigned int baseAdd)
{
    DMTimerWaitForWrite(DMTIMER_WRITE_POST_TCLR, baseAdd);

    HWREG(baseAdd + DMTIMER_TCLR) |= DMTIMER_TCLR_ST;
}

void DMTimerDisable(unsigned int baseAdd)
{
    DMTimerWaitForWrite(DMTIMER_WRITE_POST_TCLR, baseAdd);

    HWREG(baseAdd + DMTIMER_TCLR) &= ~DMTIMER_TCLR_ST;
}

void DelayS(unsigned int us)
{
    unsigned ticks_needed = us * TIMER_1S_COUNT;
    DMTimerDisable(SOC_DMTIMER_7_REGS);
    DMTimerCounterSet(SOC_DMTIMER_7_REGS, 0);
    DMTimerEnable(SOC_DMTIMER_7_REGS);
    while(HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TCRR) < ticks_needed);
    DMTimerDisable(SOC_DMTIMER_7_REGS);
}

void DelayMS(unsigned int ms)
{
    unsigned ticks_needed = ms * TIMER_1MS_COUNT;
    DMTimerDisable(SOC_DMTIMER_7_REGS);
    DMTimerCounterSet(SOC_DMTIMER_7_REGS, 0);
    DMTimerEnable(SOC_DMTIMER_7_REGS);
    while(HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TCRR) < ticks_needed);
    DMTimerDisable(SOC_DMTIMER_7_REGS);
}

void DelayMSINT(unsigned int ms)
{     
    unsigned int countVal = TIMER_OVERFLOW - (ms * TIMER_1MS_COUNT);

    /* Wait for previous write to complete */
    DMTimerWaitForWrite(DMTIMER_WRITE_POST_TCRR, SOC_DMTIMER_7_REGS);

    /* Load the register with the re-load value */
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TCRR) = countVal;

    flag_timer = false;

    /* Enable the DMTimer interrupts */
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_IRQENABLE_SET) = 0x2;

    
    /* Start the DMTimer */
    DMTimerEnable(SOC_DMTIMER_7_REGS);

    while(flag_timer == false){};

    /* Disable the DMTimer */
    DMTimerDisable(SOC_DMTIMER_7_REGS);

    /* Disable the DMTimer interrupts */
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_IRQENABLE_CLR) = 0x2;
    //printS("to contando..\n\r", 17);
}

void DelaySINT(unsigned int s)
{
    unsigned int countVal = TIMER_OVERFLOW - (s * TIMER_1S_COUNT);

    /* Wait for previous write to complete */
    DMTimerWaitForWrite(DMTIMER_WRITE_POST_TCRR, SOC_DMTIMER_7_REGS);

    /* Load the register with the re-load value */
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TCRR) = countVal;

    flag_timer = false;

    /* Enable the DMTimer interrupts */
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_IRQENABLE_SET) = 0x2;

    
    /* Start the DMTimer */
    DMTimerEnable(SOC_DMTIMER_7_REGS);

    while(flag_timer == false){};

    /* Disable the DMTimer */
    DMTimerDisable(SOC_DMTIMER_7_REGS);

    /* Disable the DMTimer interrupts */
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_IRQENABLE_CLR) = 0x2;
    //printS("to contando..\n\r", 17);
}

// =============================================================================