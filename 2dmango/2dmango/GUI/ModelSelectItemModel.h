#pragma once

#include <QAbstractTableModel>
#include <vector>
#include <string>
#include <QImage>
class ModelSelectItemModel : public QAbstractTableModel {
  Q_OBJECT
public:
  ModelSelectItemModel(QObject* parent);
  void set_data(std::vector<std::string> modelIds);
  int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
  int columnCount(const QModelIndex& parent = QModelIndex())const Q_DECL_OVERRIDE;
  QVariant data(const QModelIndex& index,int role = Qt::DisplayRole)const Q_DECL_OVERRIDE;
  QVariant headerData(int section,Qt::Orientation orientation, int role = Qt::DisplayRole)const Q_DECL_OVERRIDE;

protected:
  std::map<std::string,QImage> model_images_;
  std::map<int,int> test_map_;
  std::vector<std::string> model_ids_;
};
