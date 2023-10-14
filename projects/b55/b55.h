#ifndef __B55__
#define __B55__
#include <stdint.h>
#include <string.h>
#include "fb55ptr.h"
#include "tags.h"

#define ISO_STR_SIZE    1024

static uint8_t  b55_str[ISO_STR_SIZE];

typedef struct {
    int32_t     size;
    uint8_t b55_str[ISO_STR_SIZE];
    ST_TAGS * pstb55;
    setPtr  setIso_str;
    setIPtr setSize;
    voidPtr parse_b55_str;
} B55;

static B55 * pB55=0;
static B55 b55;


static void parse_b55_str()
{
    int32_t i,itag=0;
    uint8_t tag[2+1]={0};
    uint8_t tagTmp[8+1]={0};
    uint8_t size=0;
    uint8_t data[DATA_SIZE]={0};
    i = 0;
    while ( i <  pB55->size ){
        memset(tagTmp,0,9);
        tag[0] = pB55->b55_str[i++];
        if( ( tag[0] == 0x9F ) || ( tag[0] == 0x5F )){
            tag[1] = pB55->b55_str[i++];
            bin2str( tagTmp, tag, 2);
        }else{
            bin2str( tagTmp, tag, 1);        
        }
        size = pB55->b55_str[i++];
        memcpy(data, &pB55->b55_str[i],size);
        i += size;

        /*
        printf("Tag [%s] Size[%d] [",tagTmp,size);
        print(data,size);
        printf("]\n");
        */
        pB55->pstb55->set_code(itag, tagTmp);
        pB55->pstb55->set_size(itag, size);
        pB55->pstb55->set_data(itag, data);

        /*
        printf("Tag [%s] Size[%d] value[",pB55->pstb55->get_code(itag),pB55->pstb55->get_size(itag));
        print(pB55->pstb55->get_data(itag),size);
        printf("]\n");
        */
        
        itag++;
    }
}


void    setIso_str(uint8_t * b55_str)
{
    uint8_t ret[ISO_STR_SIZE];
    str2bin(ret, b55_str);
    memcpy(pB55->b55_str, ret, strlen(b55_str)/2); 
    pB55->size = strlen(b55_str)/2;

    printf("Bit 55 content to be parsed...\n");    
    println(pB55->b55_str,pB55->size);
    
    //pB55->pstb55->printTagTable();
    parse_b55_str();
    pB55->pstb55->printTagTable();
}

void setSize(int32_t size)
{
    pB55->size = size;
}

B55 * initB55()
{

    pB55 = &b55;
    
    pB55-> size         = 0;
    pB55->pstb55        = initST_TAGS();
    pB55->setIso_str    =  setIso_str;
    pB55->setSize       = setSize;
    pB55->parse_b55_str = parse_b55_str;
    return pB55;
}



#endif
