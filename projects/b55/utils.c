#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "utils.h"

static kcv_create_flag = 0;

static uint8_t char2bin(uint8_t  ch)
{
    if( ( ch >= 0x30 ) && ( ch <= 0x39 ) ){
        return(ch - 0x30);
    }
    switch(ch){
        case 'A':
        case 'a':
            return(10);
        case 'B':
        case 'b':
            return(11);
        case 'C':
        case 'c':
            return(12);
        case 'D':
        case 'd':
            return(13);
        case 'E':
        case 'e':
            return(14);
        case 'F':
        case 'f':
            return(15);
    }
}

static uint8_t bin2char(uint8_t  ch)
{
    if( ( ch >= 0x0 ) && ( ch <= 0x9 ) ){
        return(ch + 0x30);
    }
    switch(ch){
        case 10:
            return('A');
        case 11:
            return('B');
        case 12:
            return('C');
        case 13:
            return('D');
        case 14:
            return('E');
        case 15:
            return('F');
    }
}

void str2bin(uint8_t * ret,uint8_t * str)
{
    uint32_t i,j;
    
    for(i = 0,j=0; i < strlen(str) ; i+=2,j++){
        *(ret+j) = ( (char2bin(*(str+i))) << 4) | ( (char2bin(*(str+i+1))) & 0x0F );
    }
}

void bin2str(uint8_t * text, uint8_t * binaryStr, uint32_t length)
{
    uint32_t i;
    
    for( i = 0; i < length; i++, binaryStr++){
        uint8_t *byte = binaryStr;
        uint8_t nibleH = (*byte >> 4);
        uint8_t nibleL = (0x0F & *byte);
        
        *text++ = bin2char(nibleH);
        *text++ = bin2char(nibleL);
    }
}
 
void print(uint8_t xxc1[], uint8_t size)
{
    uint32_t i;
    for(i=0; i < size; i++){
        printf("%02X",xxc1[i]);
    }
}

void println(uint8_t xxc1[], uint8_t size)
{
    uint32_t i;
    for(i=0; i < size; i++){
        printf("%02X",xxc1[i]);
    }
    printf("\n");

}


