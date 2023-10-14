#ifndef __UTILS_H__
#define __UTILS_H__
#include <inttypes.h>

#define comp_data __DATE__
#define comp_hour __TIME__
#define version "1.0.0"



extern void str2bin(uint8_t * ret,uint8_t * str);
extern void print(uint8_t xxc1[], uint8_t size);
extern void println(uint8_t xxc1[], uint8_t size);
void bin2str(uint8_t * text, uint8_t * binaryStr, uint32_t length);

#endif

