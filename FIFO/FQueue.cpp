#include "FQueue.h"

void QFDel( QFIFO* q );

QFIFO* QFCreate()
{
   return (QFIFO*)calloc( 1, sizeof(QFIFO) );
}

int QFEmpty( QFIFO* q )
{
   return !q || !q->pHead; // 1 - pusta lub nie ustnieje
}

int QFEnqueue( QFIFO* q, QINFO* pItem )
{
   if( !q ) return 0;
   FQItem* pNew = (FQItem*)calloc( 1, sizeof(FQItem) );
   if( !pNew ) return 0;
   pNew->pInfo = pItem;
   if( QFEmpty(q) ) q->pHead = pNew;
   else             q->pTail->pNext = pNew;
   q->pTail = pNew;
   return 1;
}

QINFO* QFDequeue( QFIFO* q )
{
   if( QFEmpty(q) ) return NULL;
   QINFO* info = q->pHead->pInfo;
   QFDel( q );
   return info;
}

void QFDel( QFIFO* q )
{
   if( QFEmpty(q) )
   {
      printf( "Kolejka nie istnieje lub jest pusta\n" );
      return;
   }
   FQItem* ph = q->pHead;
   q->pHead = ph->pNext;
   free(ph);
   if( QFEmpty(q) ) q->pTail = NULL;
}

void  QFClear( QFIFO* q, void (__cdecl* freeInfo)( const void* ) )
{
   if( !q )
   {
      printf( "Kolejka nie istnieje\n" );
      return;
   }
   while( !QFEmpty(q) ) freeInfo( QFDequeue( q ) );
}

void  QFRemove( QFIFO** q, void (__cdecl* freeInfo)( const void* ) )
{
   if( !q || !*q )
   {
      printf( "Kolejka nie istnieje\n" );
      return;
   }
   QFClear( *q, freeInfo );
   free(*q);
   *q = NULL;
}