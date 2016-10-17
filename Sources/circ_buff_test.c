#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../headers/MKL25Z4.h"
#include "../headers/uart.h"
#include "../headers/circ_buff_test.h"
#include "../headers/circ.h"

circbuff *cb;

void test_initialize(void)	//wrapper function to initialize
{
	char str1[]="CB UNIT TEST: 1/5-<buff_initialize> .... PASS\n\r";
	initialize_buffer(&cb);

	print(str1);
}

void initialize_buffer(circbuff *cb)
{

	cb->buff=malloc(sizeof(circbuff));
	buff = (uint8_t*) calloc(1 , sizeof(uint8_t));
	cb->head=buff;
	cb->tail=buff;
}

void test_buff_full(void)
{
	int value;
	char passstr2[]="CB UNIT TEST: 2/5-<buff_full> .... PASS\n\r";
	char failstr2[]="CB UNIT TEST: 2/5-<buff_full> .... FAIL\n\r";
	value=buff_full(&cb);

	if(value==0)
		print(passstr2);
	else if(value==1)
		print(failstr2);
}

void test_buff_empty(void)
{
	int value;
	char passstr3[]="CB UNIT TEST: 3/5-<buff_empty> .... PASS\n\r";
	char failstr3[]="CB UNIT TEST: 3/5-<buff_empty> .... FAIL\n\r";
	value=buff_empty(&cb);

	if(value==2)
		print(passstr3);
	else if(value==3)
		print(failstr3);
}

void test_add_data(uint8_t itemtoadd)
{
	int value;
	char passstr4[]="CB UNIT TEST: 4/5-<buff_add> .... PASS\n\r";
	char failstr4[]="CB UNIT TEST: 4/5-<buff_add> .... FAIL\n\r";
	value=buff_add(&cb, itemtoadd);

	if(value==4)
		print(passstr4);
	else if(value==5)
		print(passstr4);
	else if(value==0)
		print(failstr4);
}

void test_remove_data(void)
{
	int value;
	char passstr5[]="CB UNIT TEST: 5/5-<buff_remove> .... PASS\n\r";
	char failstr5[]="CB UNIT TEST: 5/5-<buff_remove> .... FAIL\n\r";
	value=buff_remove(&cb);

	if(value!=-1)
		print(passstr5);
	else if(value==-1)
		print(failstr5);
}




