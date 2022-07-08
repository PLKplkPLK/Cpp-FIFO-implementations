#include "FQueue.h"

void  QFDel( QFIFO* q ); 
//  - wstawia NULL do pozycji tablicy, skad pobierany jest element
//  - przesuwa cyklinie indeks glowy kolejki
//  - zmniejsza ilosc elementow w kolejce

// kreowanie dynamiczne kolejki (struktury i tablicy)                                
QFIFO* QFCreate( int nSize )
{
   if( nSize < 1 ) return NULL;
   QFIFO* list = (QFIFO*)calloc( 1, sizeof(QFIFO) );
   if( !list ) return NULL;
   list->pFQItems = (QFITEM**)calloc( nSize, sizeof(QFITEM*) );
   if( !list->pFQItems ) return NULL;
   list->nMaxElem = nSize;
   return list;
}

// zwraca 1 gdy kolejka pusta, w przeciwnym wypadku 0
int QFEmpty( QFIFO* q )
{
   return !q || !q->nNoElem;
}

// wstawienie elementu do kolejki i zwrocenie 1 gdy OK i 0 gdy blad alokacji
int QFEnqueue( QFIFO* q, QFITEM* pItem )
{
   if( !q || q->nNoElem == q->nMaxElem ) return 0;
   //kolejka mo¿e przyj¹æ element
   //wpisanie elementu w tablicê
   q->pFQItems[q->nTail] = pItem;
   q->nNoElem++;
   //zmiana indeksu ogona
   //if( ++(q->nTail) == q->nMaxElem ) q->nTail = 0;
   q->nTail = ( q->nTail + 1 ) % q->nMaxElem;
   return 1;
}

// usuniecie elementu z kolejki i zwrocenie wskaznika do tego elementu (NULL - kolejka pusta), ma wywolac QFDel() 
QFITEM* QFDequeue( QFIFO* q )
{
   if( QFEmpty(q) ) return NULL;
   QFITEM* ptr = q->pFQItems[q->nHead];
   QFDel( q );
   return ptr;
}

// wstawia NULL do pozycji tablicy, skad pobierany jest element
// przesuwa cyklinie indeks glowy kolejki
// zmniejsza ilosc elementow w kolejce
void  QFDel( QFIFO* q )
{
   if( QFEmpty(q) )
   {
      printf( "Kolejka pusta lub nie istnieje.\n");
      return;
   }
   q->pFQItems[q->nHead] = NULL;
   q->nHead = ( q->nHead + 1 ) % q->nMaxElem;
   q->nNoElem--;
}

// czyszczenie kolejki, kolejke mozna uzywac
void QFClear( QFIFO* q, void (__cdecl* freeItem)( const void* ) )
{
   if( !q )
   {
      printf( "Kolejka nie istnieje \n" );
      return;
   }
   while( q->pFQItems[q->nHead] ) freeItem( QFDequeue( q ) );
   q->nHead = q->nTail = 0;
}

// czyszczenie kolejki i usuniecie wszystkich struktur danych, wyzerowanie wskaznika
void QFRemove( QFIFO** q, void (__cdecl* freeItem)( const void* ) )
{
   if( !q || !*q )
   {
      printf( "Kolejka nie istnieje\n" );
      return;
   }
   QFClear( *q, freeItem );
   free( (*q)->pFQItems );
   free( *q );
   *q = NULL;
}