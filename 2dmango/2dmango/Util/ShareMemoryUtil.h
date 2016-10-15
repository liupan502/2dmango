#ifndef MANGO_2D_SHARE_MEMORY_UTIL_H_
#define MANGO_2D_SHARE_MEMORY_UTIL_H_

#include <string>
#include <QTimer>

typedef struct DesignUpdateInfo {
  int id;
  int updater;
  int index;
  DesignUpdateInfo(int Id = 0, int Updater = -1, int Index = 0) {
    id = Id;
    updater = Updater;
    index = Index;
  }
} DesignUpdateInfo;

class DesignUpdater :public QObject {
  Q_OBJECT
    public slots:
  void UpdateDesignData();
};

const std::string  INDEX_NAME = "INDEX_NAME";
const std::string  SHARE_BUFFER_1 = "SHARE_BUFFER_1";
const std::string SHARE_BUFFER_2 = "SHARE_BUFFER_2";

void ShareMemoryBegin(DesignUpdater* updater);

void ShareMemoryEnd();


#endif
