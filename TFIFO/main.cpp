#include "FQueue.h"

#define MAX 4
#define DEBUG

void freeItem( const void* pInfo );
void PrintList( QFIFO* );

int main()
{
   //tworzenie tablicy
   QFIFO* List = QFCreate( MAX );

   //dodac do kolejki 4 elementy
   for( int i = 0; i < 4; i++ )
   {
      //tworzenie pInfo
      //informacja moga byc stringi dla kolejnych liczb calkowite od 1 . . .  (sName) (itoa)
      QFITEM* ppInfo = (QFITEM*)calloc( 1, sizeof(QFITEM) );
      ppInfo->sName = (char*)calloc( 5, sizeof(char) );
      itoa( i+11, ppInfo->sName, 10);
      ppInfo->nKey = i+1;
      if( !QFEnqueue( List, ppInfo ) ) printf(" Blad przy dodawaniu elementu.\n");
   }
#ifdef DEBUG
   printf( "Kolejka po stworzeniu i dodaniu 4 elementow:\n" );
   PrintList( List );
#endif

   //dodac jeden element - ma byc blad!!
   for( int i = 0; i < 1; i++ )
   {
      //tworzenie pInfo
      QFITEM* ppInfo = (QFITEM*)calloc( 1, sizeof(QFITEM) );
      ppInfo->sName = (char*)calloc( 5, sizeof(char) );
      itoa( i+11, ppInfo->sName, 10);
      ppInfo->nKey = i+1;
      if( !QFEnqueue( List, ppInfo ) ) printf("\nBlad przy dodawaniu elementu. Kolejka przepelniona.\n");
   }

   //usunac 3 elementy ( wypisac info )
#ifdef DEBUG
   printf( "\nUsuwanie elementow:\n" );
   for( int i = 0; i < 3; i++ )
   {
      printf( "Usuniety element %i. (nKey = %i)\n", i + 1, QFDequeue( List )->nKey );
   }
#endif

   //dodac dwa elementy
   for( int i = 0; i < 2; i++ )
   {
      //tworzenie pInfo
      QFITEM* ppInfo = (QFITEM*)calloc( 1, sizeof(QFITEM) );
      ppInfo->sName = (char*)calloc( 5, sizeof(char) );
      itoa( i+11, ppInfo->sName, 10);
      ppInfo->nKey = i+1;
      if( !QFEnqueue( List, ppInfo ) ) printf(" Blad przy dodawaniu elementu.\n");
   }
#ifdef DEBUG
   printf( "\nKolejka po  dodaniu 2 elementow:\n" );
   PrintList( List );
#endif

   //wyczyscic kolejke
   QFClear( List, freeItem );
   printf( "\nKolejka zostala wyczyszczona.\n" );

   //dodac trzy elementy
   for( int i = 0; i < 3; i++ )
   {
      //tworzenie pInfo
      QFITEM* ppInfo = (QFITEM*)calloc( 1, sizeof(QFITEM) );
      ppInfo->sName = (char*)calloc( 5, sizeof(char) );
      itoa( i+11, ppInfo->sName, 10);
      ppInfo->nKey = i+1;
      if( !QFEnqueue( List, ppInfo ) ) printf(" Blad przy dodawaniu elementu.\n");
   }
#ifdef DEBUG
   printf( "\nLista po dodaniu 3 elementow:\n" );
   PrintList( List );
#endif

   //usunac jeden (wypisac)
#ifdef DEBUG
   printf( "\nUsuwanie elementow:\n" );
   for( int i = 0; i < 1; i++ )
   {
      printf( "Usuniety element %i. (nKey = %i)\n", i + 1, QFDequeue( List )->nKey );
   }
   printf( "\nKolejka po usunieciu tego elementu:\n" );
   PrintList( List );
#endif

   //usunac CALA kolejke
   QFRemove( &List, freeItem );
   free( List );
   return 0;
}

void PrintList( QFIFO* list )
{
   int k = list->nHead;
   for( int i = 0; i < list->nNoElem; i++ ) 
   {
      printf( "%d. nKey = %d\n", i+1, list->pFQItems[k]->nKey );
      if( ++k == list->nMaxElem ) k = 0;
   }
}

void freeItem( const void* pInfo )
{
   free( ( (QFITEM*)pInfo )->sName);
   free( (QFITEM*)pInfo );
}