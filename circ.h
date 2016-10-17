//Header file for Circular Buffer
#ifndef SOURCES_CIRCBUF_H_
#define SOURCES_CIRCBUF_H_
#define MAX 5

typedef enum{
	buffer_is_full,
	buffer_is_not_full,
	buffer_is_empty,
	buffer_is_not_empty,
	add_to_buffer_success,
	add_to_buffer_success_with_wrap_around,
	read_from_buffer_success
	}buf_state;

typedef struct
{
    uint8_t *start;
    uint8_t *head;
    uint8_t *tail;
    uint32_t no_items;
    uint32_t length;
}circbuff;

circbuff tx_buffer,rx_buffer;

uint8_t *buff;
buf_state buff_full(circbuff *cb);
buf_state buff_empty(circbuff *cb);
buf_state buff_add(circbuff *cb, uint8_t item);
uint8_t buff_remove(circbuff *cb);
uint8_t* buff_initialize(circbuff *cb);
void buff_unallocate(circbuff *cb);


#endif
