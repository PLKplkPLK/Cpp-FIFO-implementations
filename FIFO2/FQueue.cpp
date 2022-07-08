#include "FQueue.h"

// tutaj tak¿e czyta³em kilka razy uwagi, ale nie wiem niestety co zmieniæ

void QFDel( QFIFO* q );

QFIFO* QFCreate()
{
   QFIFO* List = (QFIFO*)calloc( 1, sizeof(QFIFO) );
   if( !List ) return NULL;
   List->pHead = (FQItem*)calloc( 1, sizeof(FQItem) );
   if( !List->pHead ) return NULL;
   return List;
}

int QFEmpty( QFIFO* q )
{
   return !q || !(q->pHead->pNext); // 1 - pusta
}

int QFEnqueue( QFIFO* q, QINFO* pItem )
{
   if( !q ) return 0;
   FQItem* pNew = (FQItem*)calloc( 1, sizeof(FQItem) );
   if( !pNew ) return 0;
   pNew->pInfo = pItem;
   if( QFEmpty(q) ) q->pHead->pNext = pNew;
   else q->pTail->pNext = pNew;
   q->pTail = pNew;
   return 1;
}

QINFO* QFDequeue( QFIFO* q )
{
   if( QFEmpty(q) ) return NULL;
   QINFO* info = q->pHead->pNext->pInfo;
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
   FQItem* ptr = q->pHead->pNext;
   q->pHead->pNext = ptr->pNext;
   free(ptr);
   if( QFEmpty(q) ) q->pTail = q->pHead;
}

void  QFClear( QFIFO* q, void (__cdecl* freeInfo)( const void* ) )
{
   if( !q )
   {
      printf( "Kolejka nie istnieje\n" );
      return;
   }
   while( !QFEmpty(q) ) freeInfo( QFDequeue( q ) );
   q->pTail = q->pHead;
}

void  QFRemove( QFIFO** q, void (__cdecl* freeInfo)( const void* ) )
{
   if( !q || !*q )
   {
      printf( "Kolejka nie istnieje\n" );
      return;
   }
   QFClear( *q, freeInfo );
   free( (*q)->pHead );
   free(*q);
   *q = NULL;
}