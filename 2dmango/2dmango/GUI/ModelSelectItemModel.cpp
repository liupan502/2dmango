#include "ModelSelectItemModel.h"
#include "Util/LoadFileUtil.h"
#include <map>

ModelSelectItemModel::ModelSelectItemModel(QObject* parent)
  :QAbstractTableModel(parent) {

}

void ModelSelectItemModel::set_data(std::vector<std::string> modelIds) {
  model_ids_ = modelIds;
  model_images_.clear();
  for (int i = 0; i < modelIds.size(); i++) {
    if (model_images_.find(modelIds[i]) == model_images_.end()) {
      QImage img = GetModelIconImage(modelIds[i]);
      model_images_.insert(std::make_pair(modelIds[i],img));
    }
  }
}

int ModelSelectItemModel::rowCount(const QModelIndex& parent )const {
  int offset = model_ids_.size() % 2;
  int count = model_ids_.size() / 2;
  return count+offset;
}

int ModelSelectItemModel::columnCount(const QModelIndex& parent) const {
  int column_num = model_ids_.size() > 0 ? 2 : 0;
  return column_num;
}

QVariant ModelSelectItemModel::data(const QModelIndex& index, int role)const {
  if (!index.isValid() )
    return QVariant();
  int row_num = index.row();
  int col_num = index.column();
  if (2 * row_num + col_num >= model_ids_.size()) {
    return QVariant();
  }
  std::string model_id = model_ids_[2 * row_num + col_num];

  if (role == Qt::DisplayRole) {
    return QString(model_id.c_str());
  }

  if (role == Qt::DecorationRole) {
    if (model_images_.find(model_id) == model_images_.end()) {
      return QVariant();
    }
    QImage img = model_images_.find(model_id)->second;
    return img;
  }

  return QVariant();
  
}

QVariant ModelSelectItemModel::headerData(int section, Qt::Orientation orientation, int role)const {
  if (role == Qt::SizeHintRole) {
    return QSize(1, 1);
  }
  return QVariant();
}