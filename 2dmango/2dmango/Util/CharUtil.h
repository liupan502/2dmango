#ifndef MANGO_2D_CHAR_UTIL_H_
#define MANGO_2D_CHAR_UTIL_H_

void WCharToChar(const wchar_t* src, char* dest,int length = -1);

void CharToWChar(const char* src, wchar_t* dest, int length = -1);
#endif
