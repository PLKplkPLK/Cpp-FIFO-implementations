#pragma once

#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tagQFIFO
{
   QFITEM** pFQItems;
   int nHead;
   int nTail;
   int nNoElem;
   int nMaxElem;
} QFIFO;

// kreowanie dynamiczne kolejki (struktury i tablicy)          

QFIFO* QFCreate( int nSize );  // nSize  - rozmiar tablicy

// zwraca 1 gdy kolejka pusta, w przeciwnym wypadku 0
int QFEmpty( QFIFO* q );

// wstawienie elementu do kolejki
int QFEnqueue( QFIFO* q, QFITEM* pItem );

// usuniecie elementu z kolejki i zwrocenie wskaznika do tego elementu
QFITEM* QFDequeue( QFIFO* q );

// czyszczenie kolejki, kolejke mozna uzywac
void QFClear( QFIFO* q, void (__cdecl* freeItem)( const void* ) );

// czyszczenie kolejki i usuniecie wszystkich struktur danych, wyzerowanie wskaznika
void QFRemove( QFIFO** q, void (__cdecl* freeItem)( const void* ) );