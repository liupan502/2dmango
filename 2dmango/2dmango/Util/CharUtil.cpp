#include "CharUtil.h"
#include <iostream>
#include <windows.h>
#include <wchar.h>

void WCharToChar(const wchar_t* src, char* dest,int length) {
  if(length < 0)
    length = WideCharToMultiByte(CP_ACP, 0, src, wcslen(src), NULL, 0, NULL,NULL);
  memset(dest, 0, length + 1);
  WideCharToMultiByte(CP_ACP, 0, src, wcslen(src), dest, length, NULL, NULL);
  dest[length] = '\0';
}

void CharToWChar(const char* src, wchar_t* dest,int length) {
  if(length < 0)
    length = MultiByteToWideChar(CP_ACP, 0, src, strlen(src), NULL, 0);
  wmemset(dest, '\0', length + 1);
  MultiByteToWideChar(CP_ACP, 0, src, strlen(src), dest, length);
  dest[length] = '\0';
}