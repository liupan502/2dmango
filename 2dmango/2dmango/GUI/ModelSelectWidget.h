#pragma once
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTableView>
#include "Entity/ModelData.h"
#include "BaseDetailActionWidget.hpp"
#include "ModelSelectItemDelegate.h"
#include "ModelSelectItemModel.h"


class ModelSelectWidget : public BaseDetailActionWidget {

Q_OBJECT
public:
  ModelSelectWidget(QWidget * parent);
  void Init(std::map<std::string,std::string> parameters);
  //ModelSelectWidget(std::vector<ModelData*>)
private:
  
  QTableView* models_table_;

 signals:
  void test_signals();

 public slots:
  void model_selected(const QModelIndex &index);
  void test_slots();
};

/*class ModelWidget :public QWidget {
public:
  ModelWidget();
private:

};*/
