#include "MKL25Z4.h"
#include<stdio.h>
#include <math.h>
#include <string.h>
#include <log.h>








void uart_init()//uint32_t baudRate)
{

	uint16_t baud_divisor;

    __disable_irq();
	//Sets gate clock  for PORTA
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

	//Enables clock for UART0; source as MCGCLKFLL
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);

	// Sets for UART0 mode
	PORTA_PCR1 = PORT_PCR_MUX(2);
	PORTA_PCR2 = PORT_PCR_MUX(2);

	// Disables tx and rx before editing registers
	UART0_C2=0x00;
	UART0_C1=0x00;

    /* Calculate baud_divisor for sbr register and set baud rate */
	//baud_divisor= (uint16_t)(DEFAULT_SYSTEM_CLOCK/(baudRate*16));
	UART0_BDH |= 0x00;//(baud_divisor >> 8) & UART0_BDH_SBR_MASK;
	UART0_BDL |= 0x17;//(baud_divisor & UART0_BDL_SBR_MASK);


//	UART_C2_REG(UART0_BASE_PTR) |= UART_C2_TIE_MASK;//Setup receiver interrupt
	//UART_C2_REG(UART0_BASE_PTR) |= UART_C2_RIE_MASK;
	UART_C2_REG(UART0_BASE_PTR) |= (UART_C2_TE_MASK | UART_C2_RE_MASK );

	__enable_irq();

	//Enabling NVIC and CPU interrupts
	NVIC_EnableIRQ(UART0_IRQn);
	//Switch on transmitter and receiver

}





//void UART0_IRQHandler()
//{
//	__disable_irq();
//
//
//
//	uint8_t status;
//
//    status = UART0_S1;
//
//    if(status & UART_S1_TDRE_MASK)
//    {
//
//        if(handler_i<=6)
//        {
//    	UART0_D=*(p+handler_i);
//    	handler_i++;
//        }
//        else
//        {
//        	UART_C2_REG(UART0_BASE_PTR)  &= ~UART_C2_TIE_MASK;
//
//        	handler_i=0;
//        }
//    }
//
//    if(status & UART_S1_RDRF_MASK)
//    {
//        if(handler_j<=6)
//        {
//    	*(arr+handler_j)=UART0_D;
//    	handler_j++;
//        }
//        else
//        {
//        	UART_C2_REG(UART0_BASE_PTR) &= ~UART_C2_RIE_MASK;
//        	handler_j=0;
//        }
//    }
//   __enable_irq();
//}
//
