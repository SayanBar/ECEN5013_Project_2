#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "../headers/log.h"



char * ftoa(char *s, double n) {
    // handle special cases
    if (isnan(n)) {
        strcpy(s, "nan");
    } else if (isinf(n)) {
        strcpy(s, "inf");
    } else if (n == 0.0) {
        strcpy(s, "0");
    } else {
        int digit, m, m1;
        char *c = s;
        int neg = (n < 0);
        if (neg)
            n = -n;
        // calculate magnitude
        m = log10(n);
        int useExp = (m >= 14 || (neg && m >= 9) || m <= -9);
        if (neg)
            *(c++) = '-';
        // set up for scientific notation
        if (useExp) {
            if (m < 0)
               m -= 1.0;
            n = n / pow(10.0, m);
            m1 = m;
            m = 0;
        }
        if (m < 1.0) {
            m = 0;
        }
        // convert the number
        while (n > PRECISION || m >= 0) {
            double weight = pow(10.0, m);
            if (weight > 0 && !isinf(weight)) {
                digit = floor(n / weight);
                n -= (digit * weight);
                *(c++) = '0' + digit;
            }
            if (m == 0 && n > 0)
                *(c++) = '.';
            m--;
        }
        if (useExp) {
            // convert the exponent
            int i, j;
            *(c++) = 'e';
            if (m1 > 0) {
                *(c++) = '+';
            } else {
                *(c++) = '-';
                m1 = -m1;
            }
            m = 0;
            while (m1 > 0) {
                *(c++) = '0' + m1 % 10;
                m1 /= 10;
                m++;
            }
            c -= m;
            for (i = 0, j = m-1; i<j; i++, j--) {
                // swap without temporary
                c[i] ^= c[j];
                c[j] ^= c[i];
                c[i] ^= c[j];
            }
            c += m;
        }
        *(c) = '\0';
    }
    return s;
}



void log1(float n, char *res,uint8_t len)
{
	   uint8_t i=0,j=0;
       char *p=ftoa(res,n);
       char *s2="This is an integer number:";
       while(*(s2+j)!='\0')
              		{
                      while(!(UART0_S1 & UART_S1_TDRE_MASK));
                      	//UART0_S1 &= ~UART_S1_TDRE_MASK;
                      	UART0_D= *(s2+j);
                      	j++;

                      	//while(UART0_S1 & UART_S1_TDRE_MASK);
                      	//for(j=0;j<500;j++);
                    }

       while(*(p+i)!='\0')
       		{
               while(!(UART0_S1 & UART_S1_TDRE_MASK));
               	//UART0_S1 &= ~UART_S1_TDRE_MASK;
               	UART0_D= *(p+i);
               	i++;

               	//while(UART0_S1 & UART_S1_TDRE_MASK);
               	//for(j=0;j<500;j++);
            }


}

void log0(char *str1,uint8_t len)
{
	//UART_C2_REG(UART0_BASE_PTR) |= UART_C2_TIE_MASK;
#if F
	uint8_t i=0,j=0;
		//char str1[100]="Testing123, Serial Print Test, no params";
		//char var='\n';
		while(*(str1+i)!='\0')
		{
        while(!(UART0_S1 & UART_S1_TDRE_MASK));
        	//UART0_S1 &= ~UART_S1_TDRE_MASK;
        	UART0_D= *(str1+i);
        	i++;
        	//UART0_D='\n';

        	//while(UART0_S1 & UART_S1_TDRE_MASK);
        	//for(j=0;j<500;j++);
        }
#endif

		#if NF
    uint8_t i;
    for(i=0;i<len;i++)
    {
        printf("%c",data[i]);
    }
        #endif
}


uint8_t itoa(int x, char *s)
{
	int i=0;
	char character;
	while(x!=0)
	{
	character= (x%10)-'0';
	x=x/10;
	*(s+i) = character;
	i++;
	}

	if((fpart!=0) && (state==1) )
	   *(s+i)='\0';

	if((fpart==0) && (state==0))
			*(s+i)='\0';

	return i;
}

void print(char *str)
{
	uint8_t i=0;
	while((*(str+i))!='\0')
			{
					while(UART0_S1 & UART_S1_TDRE_MASK);
					UART0_D=*(str+i);
					i++;
			}
}
