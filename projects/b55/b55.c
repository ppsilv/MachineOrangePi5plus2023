#include <stdio.h>

#include "/home/pdsilva/projects/utils/utils.h"
#include "tags.h"
#include "b55.h"

uint8_t iso_str[4096]={"9F34031E03009F2608D5EE0F1882198E0F9F2701409F10120114904303248000000000000000000001FF9F3704335342369F3602003195050000000000820219819F33036020C89F1A0208409F3501239F1E085445524D313130339F03060000000000009A032101059C01009F02060000000015005F2A0208409F5301468407A00000000410109F09020002"};


int main(int argc, void * argv[])
{
    char *var="9F31";

    B55 *pB55 = initB55();
    printf("B55 analisys...\n");
    //printf("B55 analisys...\n[%s]\n",iso_str);
    //uint8_t * ret[4096];
    
    //str2bin(ret, iso_str);
    //print(ret, strlen(iso_str)/2);
    
    
    pB55->setIso_str(iso_str);
    
    //pB55->parse_b55_str();

    
    //printf("Tag code[%s]\n",pstb55->get_code(11));
    //printf("Tag size[%d]\n",pstb55->get_size(21));
    //printf("Tag desc[%s]\n",pstb55->get_desc(20));
    //printf("Tag data[%s]\n",pstb55->get_data(11));
    
    return(0);
}
