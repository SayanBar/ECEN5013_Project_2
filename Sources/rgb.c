#include "../headers/MKL25Z4.h"
#include <math.h>
#include "../headers/rgb.h"




uint16_t  data=100;
LED Color_Number=OFF;

void uart_init()
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


UART_C2_REG(UART0_BASE_PTR) |= UART_C2_TIE_MASK;//Setup receiver interrupt
	UART_C2_REG(UART0_BASE_PTR) |= UART_C2_RIE_MASK;
	UART_C2_REG(UART0_BASE_PTR) |= (UART_C2_TE_MASK | UART_C2_RE_MASK );

	__enable_irq();

	//Enabling NVIC and CPU interrupts
	NVIC_EnableIRQ(UART0_IRQn);
	//Switch on transmitter and receiver

}
void LED_Initialize()
{
    SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM2_MASK;    //initialize TPM2 for red and green and TPM0 for blue
	SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM0_MASK;
    SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(1);


    TPM0_BASE_PTR->SC = TPM_SC_CMOD(1) | TPM_SC_PS(7);
    TPM0_BASE_PTR->MOD = 1875;

    TPM2_BASE_PTR->SC = TPM_SC_CMOD(1) | TPM_SC_PS(7);  // initialize the mod data to 1875
    TPM2_BASE_PTR->MOD = 1875;

    SIM_BASE_PTR->SCGC5 |=  0x400;     //define clock sources for the TPM mode
    SIM_BASE_PTR->SCGC5 |= 0x1000;

    PORTB_BASE_PTR->PCR[18] = PORTB_BASE_PTR->PCR[19] = PORT_PCR_MUX(3);
    PORTD_BASE_PTR->PCR[1]=PORT_PCR_MUX(4);

      TPM2_BASE_PTR->CONTROLS[0].CnSC =  0x20 | 0x4;
      TPM2_BASE_PTR->CONTROLS[1].CnSC =  0x20 | 0x4; ;
      TPM0_BASE_PTR->CONTROLS[1].CnSC =  0x20 | 0x4; ;
}

void LED_Modify(uint8_t input)
{
      if(input=='a' && data<500)    // increment data for brightness increase
      {
    	  data+=100;

      }
      else if(input=='d' && data>0)  //decrement data for brightness decrease
       {
             data-=100;
        }

      else if(input=='w') // set input 'a' for color change from red to white
            {
    	  Color_Number++;
          	 if(Color_Number>=7)
          		Color_Number=0;

            }
      else if(input=='s') // set input 'a' for color change from white to red
             {
    	  Color_Number--;
               if(Color_Number<=0)
            	 Color_Number=7;
              }
      Brightness_Control(Color_Number, data);

}

void Brightness_Control(LED Color_Number, uint16_t Bright)
{
	 if(Color_Number==BLUE)
	 {
		TPM2_BASE_PTR->CONTROLS[1].CnV = 0;
		TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
		TPM0_BASE_PTR->CONTROLS[1].CnV = Bright;
	 }
	 else if(Color_Number==GREEN)
	 {
	 	TPM2_BASE_PTR->CONTROLS[1].CnV = Bright;
	 	TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
	 	TPM0_BASE_PTR->CONTROLS[1].CnV = 0;
	 }
	 else if(Color_Number==RED)					// for each Color_Number combination turn on and off the rgb colours
     {
 	    TPM2_BASE_PTR->CONTROLS[1].CnV = 0;
 	    TPM0_BASE_PTR->CONTROLS[1].CnV = 0;
 	    TPM2_BASE_PTR->CONTROLS[0].CnV = Bright;
 	 }


	else if(Color_Number==CYAN)
	{
	    TPM2_BASE_PTR->CONTROLS[1].CnV = TPM0_BASE_PTR->CONTROLS[1].CnV = Bright;
	    TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
	}
	else if(Color_Number==YELLOW)
	{
	    TPM0_BASE_PTR->CONTROLS[1].CnV = 0;
	    TPM2_BASE_PTR->CONTROLS[0].CnV = TPM2_BASE_PTR->CONTROLS[1].CnV = Bright;
	}

	else if(Color_Number==MAGENTA)                 //for dual Color_Number combination turn two of them on
	{
		TPM2_BASE_PTR->CONTROLS[1].CnV = 0;
		TPM2_BASE_PTR->CONTROLS[0].CnV = TPM0_BASE_PTR->CONTROLS[1].CnV = Bright;
	}
	else if(Color_Number==WHITE)				//for white turn all the colours on
	{
	    TPM2_BASE_PTR->CONTROLS[1].CnV = TPM2_BASE_PTR->CONTROLS[0].CnV=TPM0_BASE_PTR->CONTROLS[1].CnV = Bright;
	}
	else
	{
		TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
		TPM0_BASE_PTR->CONTROLS[1].CnV = 0;
	    TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
	}
}

void UART0_IRQHandler()
{
		__disable_irq();

	    uint8_t input;

		uint8_t status;

	    status = UART0_S1;
	   UART0_S1=status;

	    //if(status & UART_S1_TDRE_MASK);

	    if(status & UART_S1_RDRF_MASK)
	    {
	        input=UART0_D;
	    	LED_Modify(input);
	    }
	   __enable_irq();

}

void main()
{

	LED_Initialize();
	uart_init();
	while(1);
}

