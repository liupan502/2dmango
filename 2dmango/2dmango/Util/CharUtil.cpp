#include "CharUtil.h"
#include <iostream>
#include <windows.h>
#include <wchar.h>

void WCharToChar(const wchar_t* src, char* dest) {
  int len = WideCharToMultiByte(CP_ACP, 0, src, wcslen(src), NULL, 0, NULL,NULL);
  memset(dest, 0, len + 1);
  WideCharToMultiByte(CP_ACP, 0, src, wcslen(src), dest, len, NULL, NULL);
  dest[len] = '\0';
}

void CharToWChar(const char* src, wchar_t* dest) {
  int len = MultiByteToWideChar(CP_ACP, 0, src, strlen(src), NULL, 0);
  wmemset(dest, '\0', len + 1);
  MultiByteToWideChar(CP_ACP, 0, src, strlen(src), dest, len);
  dest[len] = '\0';
}