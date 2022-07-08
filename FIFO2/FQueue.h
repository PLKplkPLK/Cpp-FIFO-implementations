#pragma once

#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tagFQItem
{
   QINFO* pInfo;
   tagFQItem* pNext;
} FQItem;

typedef struct tagQFIFO
{
   FQItem* pHead;
   FQItem* pTail;
} QFIFO;

// kreowanie dynamiczne kolejki
QFIFO* QFCreate();

// zwraca 1 gdy kolejka pusta, w przeciwnym wypadku 0
int QFEmpty( QFIFO* q );

// wstawienie elementu do kolejki i zwrocenie 1 gdy OK i 0 gdy blad alokacji
int QFEnqueue( QFIFO* q, QINFO* pItem );

// usuniecie elementu z kolejki i zwrocenie wskaznika do tego elementu (NULL - kolejka pusta)
// ma wywolac QFDel()
QINFO* QFDequeue( QFIFO* q );

// czyszczenie kolejki, kolejke mozna uzywac dalej
void  QFClear( QFIFO* q, void (__cdecl* freeInfo)( const void* ) );

// czyszczenie kolejki i usuniecie wszystkich struktur danych, wyzerowanie kolejki
void  QFRemove( QFIFO** q, void (__cdecl* freeInfo)( const void* ) );