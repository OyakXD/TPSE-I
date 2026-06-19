#ifndef TIMER_H
#define TIMER_H

/* Função que inicia toda a configuração do DMTIMER*/
extern void timerInit(void);

/* Função para ativar o clock de um DMTIMERx [0,2..7] */
extern void enableClockDMTIMERx(volatile unsigned int numDMTIMER);

/* Retorna o status do TPWS Register */
extern unsigned int DMTimerWritePostedStatusGet(unsigned int baseAdd);

/* Seta o valor inicial do contador */
extern void DMTimerCounterSet(unsigned int baseAdd, unsigned int counter);

/* Lê o valor do contador */
extern unsigned int DMTimerCounterGet(unsigned int baseAdd);

/* Inicia o timer */
extern void DMTimerEnable(unsigned int baseAdd);

/* Para o timer */
extern void DMTimerDisable(unsigned int baseAdd);

/* Função delay em segundo*/
extern void DelayS(unsigned int us);

/* Função delay em milisegundos*/
extern void DelayMS(unsigned int ms);

/* Função delay em milisegundos com interrupção */
extern void DelayMSINT(unsigned int ms);

/* Função delay em segundos com interrupção */
extern void DelaySINT(unsigned int s);

#endif // TIMER_H