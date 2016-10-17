#include "../headers/MKL25Z4.h"
#include "../headers/memory.h"
#include <time.h>
#include <string.h>
#include <stdint.h>
#include "../headers/mcg.h"

#define buffer		5000

void start_timer(void);
void stop_timer(void);

volatile uint32_t counter = 0;

void print_character(int c);

void uart_init()
{

	//uint16_t baud_divisor;

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


//UART_C2_REG(UART0_BASE_PTR) |= UART_C2_TIE_MASK;//Setup receiver interrupt
	//UART_C2_REG(UART0_BASE_PTR) |= UART_C2_RIE_MASK;
	UART_C2_REG(UART0_BASE_PTR) |= (UART_C2_TE_MASK | UART_C2_RE_MASK );

	__enable_irq();

	//Enabling NVIC and CPU interrupts
//	NVIC_EnableIRQ(UART0_IRQn);
	//Switch on transmitter and receiver

}




void print_character(int c)
	{
		while(!(UART0->S1 & 0xC0));
		 UART0->D = c;

	}


void start_timer()
{
	// PLL clock select
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
	SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);

	// Select MCGPLLCLK/2
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);

	// Enable TPM clock
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;

	//Nullify the control registers to ensure counter is not running

	TPM0_SC = 0;
	TPM0_CONF = 0;

	//Set prescalar to 1 when counter is disabled
	TPM0_SC = TPM_SC_PS(0);

	// Setting modulo value to set 10us as the execution timer
	TPM0_MOD = 480;

	//Enable Interrupts for the Timer Overflow
		TPM0_SC |= TPM_SC_TOIE_MASK;
	//Enable the TPM Counter
	TPM0_SC |= TPM_SC_CMOD(1);

	//NVIC_ClearPendingIRQ(TPM0_IRQn);
	NVIC_EnableIRQ(TPM0_IRQn);


}

void stop_timer()
{
	NVIC_DisableIRQ(TPM0_IRQn);//Disable the interrupt
	TPM0_SC = 0;
	TPM0_CONF = 0;
}

void TPM0_IRQHandler()
{
	if(TPM0_SC & TPM_SC_TOF_MASK)
	{
		counter++;//incrementing counter to note the number of overflows
		TPM0_SC |= TPM_SC_TOF_MASK;//clearing the overflow mask
	}
}

void main(void)
{
	uint32_t x = 0;
		double y = 0;
	pll_init(8000000, LOW_POWER, CRYSTAL,4,24,MCGOUT);
     uart_init();
	uint8_t dst[buffer];
	uint8_t src[buffer];
	uint32_t length;
	length = buffer;


	start_timer();
	my_memmove(src,dst,length);
	stop_timer();

	x = counter*480 + TPM0_CNT;
	y = (x / 48000000.00);

	print_character(x);
	//return 0;
}
