#pragma once

typedef struct tagQInfo
{
   char* sName;
   int nKey;
} QInfo;

#define QFITEM QInfo

void freeInfo( const void* );