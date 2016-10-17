#include "../headers/MKL25Z4.h"
#include "../headers/uart.h"
#include "../headers/compiler_switch.h"
#include "../headers/circ_buff_test.h"
#include "../headers/circ.h"
#include "../headers/rgb.h"
#include "../headers/log.h"
#define test_function 1

int main(void)
{
	__disable_irq();

	uart_init(); //initialize UART0
	__enable_irq(); //enable interrupt
	uint8_t tx_string[100]="Enter a,s,d,w for led control and 't' for echo mode\n\r",rx_string[100]="0";
	print(tx_string); //print string on UART
	Initialize_LED();	//Initialize LED program
	uint32_t i=0;

	   //Circular Buffer Test Functions
#ifdef test_function
		    void test_initialize(void); //wrapper function to test initialize
		    void test_buff_full(void);	//wrapper function to test the full buffer case
		    void test_buff_empty(void);	//wrapper function to test the empty buffer case
		    void test_add_data(uint8_t itemtoadd);	//wrapper function to test the add data case
		    void test_remove_data(void);	//wrapper function to test the remove data test
#endif

		    //Log functions
#ifndef Log_function

		  	char str1[]="Testing123, Serial Print Test, no params";
		    char str2[]="This is an integer number:";
		    char str3[]="This is a floating point number:";
		    float var2=200;
		    float var3=4096;
		    float var4=123456;
		    float var5=1543.321;

	#if F   //FRDM UART is enabled
	    log0(&str1,40);	//print first string

	    print('\r\n'); //go to new line
	    print('\r');

	    log1(&str2,var2,0);	//print second string

	    print('\r\n');
	    print('\r');

	    log1(&str2,var3,0);	//print third string

	    print('\r\n');
	    print('\r');

	    log1(&str2,var4,0);	//print fourth string

	    print('\r\n');
	    print('\r');

	    log1(&str3,var5,3);	//print fifth string

	    print('\r\n');
	    print('\r');


	#endif

	#if NF   //BBB PRINTF

	    log0(&str1,40);
	    printf("\n\n");

	    log1(&str2,var2,0);
	    printf("\n");

	    log1(&str2,var3,0);
	    printf("\n");

	    log1(&str2,var4,0);
	    printf("\n");

	    log1(&str3,var5,3);
	    printf("\n");

	#endif


#endif

	while(1)
	{
		buf_state ec=buff_empty(&rx_buffer);

		if(ec==buffer_is_not_empty)  // check for buffer status
		{
			uint8_t inp=buff_remove(&rx_buffer),state;
			if(inp=='t' || inp==0xd)  // check for input from keyboard
				state=inp;

			if(state=='t')
			{
				rx_string[i] = inp;
				i++;
			}
		    else if(state==0xd)
			{
			    state=0;
			    i=0;
			    print(rx_string);
			}
		    else if((inp=='a'|| inp=='s' || inp=='w' || inp=='d')) // change brightness and led colour depending on keyboard input
		    	LED_Modify(inp);
		 }

	 }

}
