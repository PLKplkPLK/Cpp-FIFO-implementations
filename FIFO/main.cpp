#include "FQueue.h"

#define DEBUG

void PrintList( FQItem* );

int main()
{
   //- dodac do kolejki 4 elementy
   //- dodac jeden element - ma byc blad!!
   QFIFO* List = QFCreate();
   if( !List )
   {
      perror( "Could not create list, main#14" );
      return 1;
   }
   for( int i = 0; i < 4; i++ )
   {
      //tworzenie pInfo
      //- informacja moga byc stringi dla kolejnych liczb calkowite od 1 . . .  (sName) (itoa)
      QINFO* ppInfo = (QINFO*)calloc( 1, sizeof(QINFO) );
      ppInfo->sName = (char*)calloc( 5, sizeof(char) );
      itoa( i+10, ppInfo->sName, 10);
      ppInfo->nKey = i+1;
      if( !QFEnqueue( List, ppInfo ) )
      {
         printf("Error adding item");
         return 1;
      }
   }
#ifdef DEBUG
   printf( "Lista po stworzeniu i dodaniu 4 elementow:\n" );
   PrintList( List->pHead );
#endif

   //- usunac 3 elementy (wypisac info)
#ifdef DEBUG
   printf( "\nUsuwanie elementow:\n" );
   for( int i = 0; i < 3; i++ )
   {
      printf( "Usuniety element %i (nKey = %i)\n", i + 1, QFDequeue( List )->nKey );
   }
#endif

   //- dodac dwa elementy
   for( int i = 0; i < 2; i++ )
   {
      //tworzenie pInfo
      QINFO* ppInfo = (QINFO*)calloc( 1, sizeof(QINFO) );
      ppInfo->sName = (char*)calloc( 5, sizeof(char) );
      itoa( i+10, ppInfo->sName, 10);
      ppInfo->nKey = i+1;
      if( !QFEnqueue( List, ppInfo ) )
      {
         printf("Error adding item");
         return 1;
      }
   }
#ifdef DEBUG
   printf( "\nLista po dodaniu dwoch elementow:\n" );
   PrintList( List->pHead );
#endif

   //- wyczyscic kolejke
   QFClear( List, freeInfo );
#ifdef DEBUG
   printf( "\nLista zostala oczyszczona.\n" );
#endif

   //- dodac trzy elementy
   for( int i = 0; i < 3; i++ )
   {
      //tworzenie pInfo
      QINFO* ppInfo = (QINFO*)calloc( 1, sizeof(QINFO) );
      ppInfo->sName = (char*)calloc( 5, sizeof(char) );
      itoa( i+10, ppInfo->sName, 10);
      ppInfo->nKey = i+1;
      if( !QFEnqueue( List, ppInfo ) )
      {
         printf("Error adding item");
         return 1;
      }
   }
#ifdef DEBUG
   printf( "\nLista po dodaniu 3 elementow:\n" );
   PrintList( List->pHead );
#endif

   //- usunac jeden (wypisac)
#ifdef DEBUG
   printf( "\nUsunieto element %i (nKey = %i)\n", 1, QFDequeue( List )->nKey );
#endif

   //- usunac CALA kolejke
   QFRemove( &List, freeInfo );
#ifdef DEBUG
   printf( "\nLista zostala usunieta." );
#endif

   return 0;
}

void freeInfo( const void* pInfo )
{
   free( ( (QINFO*)pInfo )->sName);
   free( (QINFO*)pInfo );
}

void PrintList( FQItem* qr )
{
   int i = 1;
   while( qr )
   {
      printf( "%d. nKey = %d\n", i++, qr->pInfo->nKey );
      qr = qr->pNext;
   }
}