#ifndef INTERRUPT_H
#define INTERRUPT_H

// Função que inicia as interrupções no AM335x
extern void intAINTCInit(void);

// Rotina de interrupção
extern void ISR_Handler(void);

// Função que trata as interrupção de gpio
extern void gpioIsr(void);

// Configurações de interrupção de gpio
extern void gpioInterruptInit(void);

// Função que trata as interrupção do DMTIMER
extern void DMTimerIsr(void);

// Configurações de interrupção do dmtimer
extern void dmTimerInit(void);

#endif // INTERRUPT_H