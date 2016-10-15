#include "ShareMemoryUtil.h"
#include <windows.h>
#include <wchar.h>
#include "Entity/DesignDataWrapper.h"
#include "CharUtil.h"
#include <QJsonObject>

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
  DesignUpdateInfo* info = GetUpdateInfo();
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  int id = instance->DesignDataId();
  if (id == info->id) {
    return;
  }
  else if (id > info->id) {
    std::string json_str = instance->GetDesignData();    
    
    std::string buffer_name = "";
    if (info->index == 1) {
      buffer_name = SHARE_BUFFER_1;
    }
    else {
      buffer_name = SHARE_BUFFER_2;
    }

    wchar_t tmp[256];
    CharToWChar(buffer_name.c_str(), tmp);
    LPVOID h_buffer_map = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, tmp);
    if (h_buffer_map != NULL) {
      LPVOID pBuffer = ::MapViewOfFile(h_buffer_map, FILE_MAP_ALL_ACCESS, 0, 0, 0);
      int data_size = json_str.length();       
      wchar_t* data_buffer = (wchar_t*)malloc(sizeof(wchar_t)*(data_size+1));      
      CharToWChar(json_str.c_str(), data_buffer);
      wmemcpy((wchar_t*)pBuffer,data_buffer,data_size+1);      
      free(data_buffer);      
    }

    info->id = id;
    info->updater = 0;
    if (info->index == 1) {
      info->index = 2;
    }
    else {
      info->index = 1;
    }



  }
  else {

  }
}

DesignUpdateInfo* DesignUpdater::GetUpdateInfo() {
  DesignUpdateInfo* info = NULL;
  wchar_t tmp[256];
  CharToWChar(INDEX_NAME.c_str(), tmp);
  LPVOID h_map = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, tmp);
  if (h_map != NULL) {
    LPVOID pBuffer = ::MapViewOfFile(h_map, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    info = (DesignUpdateInfo*)pBuffer;
  }
  return info;
}