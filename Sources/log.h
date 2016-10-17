#ifndef SOURCES_LOG_H_
#define SOURCES_LOG_H_

#define value 400
float fpart;
uint8_t state=0;
uint8_t flag1=0;

static double PRECISION = 0.0001;
char str[200];

uint8_t itoa(int x, char *s);
void log1(float n, char *res,uint8_t);
void log0(char *,uint8_t);
void print(char *str);


#endif
