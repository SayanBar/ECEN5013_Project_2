#ifndef SOURCES_CIRC_BUFF_TEST_H_
#define SOURCES_CIRC_BUFF_TEST_H_

void test_initialize(void);
void test_buff_full(void);
void test_buff_empty(void);
void test_add_data(uint8_t itemtoadd);
void test_remove_data(void);
void initialize_buffer(circbuff *cb);
#endif
