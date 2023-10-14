#ifndef __TAGS_HH__
#define __TAGS_HH__
#include <stdint.h>
#include "fb55ptr.h"


#define MAX_TAGS    40
#define DATA_SIZE   512

#define ASSERT(expr) \
    if ((expr>(MAX_TAGS-1))) \
        return "0"
 

typedef struct{
    uint8_t     tag_code[8+1];
    uint8_t     desc[128+1];
    uint32_t    size;
    uint8_t     data[DATA_SIZE];    
} ST_TAG;

typedef struct {
    ST_TAG      tags[MAX_TAGS];
    setSPtr     set_code;
    getSPtr     get_code;
    setIPtr     set_size;
    getIPtr     get_size;
    setSPtr     set_desc;
    getSPtr     get_desc;
    setSPtr     set_data;
    getSPtr     get_data;
    voidPtr     printTagTable;
} ST_TAGS;

static ST_TAGS * pST_TAGS=0;
static ST_TAGS stb55;

static void set_code(uint8_t index,uint8_t * tag_code)
{
        ASSERT(index);
        //printf("  (%s)   ",tag_code);
        memcpy(pST_TAGS->tags[index].tag_code, tag_code, strlen(tag_code));    
       //printf("Metodo set index [%d]: [%s] [%s]\n",index,tag_code,pST_TAGS->tags[index].tag_code);
}

uint8_t * get_code(uint8_t index)
{
    ASSERT(index);
    return pST_TAGS->tags[index].tag_code;
}

void set_desc(uint8_t index, uint8_t * desc)
{
    ASSERT(index);
    memcpy(pST_TAGS->tags[index].desc, desc, strlen(desc));    
}

uint8_t * get_desc(uint8_t index)
{
    ASSERT(index);
    return pST_TAGS->tags[index].desc;
}

void set_size(uint8_t index, uint32_t size)
{
    ASSERT(index);
    pST_TAGS->tags[index].size = size;    
}

uint32_t * get_size(uint8_t index)
{
    ASSERT(index);
    return pST_TAGS->tags[index].size;
}
void set_data(uint8_t index, uint8_t * data)
{
    ASSERT(index);
    memcpy(pST_TAGS->tags[index].data, data, strlen(data));    
}

uint8_t * get_data(uint8_t index)
{
    ASSERT(index);
    return pST_TAGS->tags[index].data;
}

void printTagTable()
{
    uint32_t index=0;
    printf("********************** The tags found *****************************\n");
    while( 1 ){
        if( strlen( pST_TAGS->get_code(index) ) == 0 ){
            break;
        }
        printf("Tag [% 4s] Size[%02d] value[",pST_TAGS->get_code(index), pST_TAGS->get_size(index));
        print(pST_TAGS->get_data(index),pST_TAGS->get_size(index));
        printf("]\n");
        index++;    
    }
    printf("*******************************************************************\n");
}

ST_TAGS * initST_TAGS()
{
    memset((char*)&stb55,0,sizeof(ST_TAGS));
    
    pST_TAGS = &stb55;
    pST_TAGS->set_code=set_code;
    pST_TAGS->get_code=get_code;
    pST_TAGS->set_size=set_size;
    pST_TAGS->get_size=get_size;
    pST_TAGS->set_desc=set_desc;
    pST_TAGS->get_desc=get_desc;
    pST_TAGS->set_data=set_data;
    pST_TAGS->get_data=get_data;
    pST_TAGS->printTagTable=printTagTable;
    return &stb55;
}

#endif
