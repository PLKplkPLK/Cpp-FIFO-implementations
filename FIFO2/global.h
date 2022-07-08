#pragma once

typedef struct tagQInfo
{ 
  char* sName;
  int   nKey;
} QInfo;

#define QINFO QInfo

void freeInfo( const void* );