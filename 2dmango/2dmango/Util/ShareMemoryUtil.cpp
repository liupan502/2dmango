#include "ShareMemoryUtil.h"
#include <windows.h>
#include <wchar.h>
#include "CharUtil.h"

void SetupTimer(DesignUpdater* updater) {
  QTimer timer;
  QObject::connect(&timer, SIGNAL(timeout()), updater, SLOT(UpdateDesignData()));
  timer.start(1000);
}

void ShareMemoryBegin(DesignUpdater* updater) {
 
  wchar_t tmp[256];

  DesignUpdateInfo* info = new DesignUpdateInfo();
  CharToWChar(INDEX_NAME.c_str(),tmp);
  LPVOID h_index_map = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(DesignUpdateInfo), tmp);
  if (h_index_map != NULL) {
    LPVOID pBuffer = ::MapViewOfFile(h_index_map, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    memcpy(pBuffer, info, sizeof(DesignUpdateInfo));
    DesignUpdateInfo* test = (DesignUpdateInfo*)(pBuffer);    
  }
  delete info;
  
  CharToWChar(SHARE_BUFFER_1.c_str(), tmp);
  LPVOID h_buffer1_map = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(wchar_t)*1024*1024, tmp);
  if (h_buffer1_map != NULL) {

  }

  CharToWChar(SHARE_BUFFER_2.c_str(), tmp);
  LPVOID h_buffer2_map = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(wchar_t) * 1024 * 1024, tmp);
  if (h_buffer2_map != NULL) {

  }

  //SetupTimer(updater);
}

void ShareMemoryEnd() {

}

void DesignUpdater::UpdateDesignData() {
  int a = 0;
  int b = 0;
}