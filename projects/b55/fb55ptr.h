#ifndef __FUNC_POINTER__
#define __FUNC_POINTER__

#include <stdio.h>

typedef void (*setCodePtr)(uint8_t ,uint8_t *);
typedef uint8_t * (*getCodePtr)(uint8_t);
typedef void (*setSizePtr)(uint8_t ,int);
typedef int (*getSizePtr)(uint8_t );
typedef void (*setDataPtr)(uint8_t ,uint8_t *);
typedef uint8_t (*getDataPtr)(uint8_t );
/*
typedef void (*setPtr)(uint8_t *);
typedef int  (*getiPtr)(void);
typedef uint8_t * (*getsPtr)(void);
*/

typedef void      (*voidPtr)(void);
typedef void      (*setPtr)(uint8_t *);
typedef void      (*setSPtr)(uint8_t ,uint8_t *);
typedef void      (*setIPtr)(uint8_t ,int);
typedef int       (*getIPtr)(uint8_t);
typedef uint8_t * (*getSPtr)(uint8_t);


#endif
