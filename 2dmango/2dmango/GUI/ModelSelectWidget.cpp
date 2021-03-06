#include "ModelSelectWidget.h"
#include "Util/LoadFileUtil.h"
#include <QTextEdit>
#include "Entity/ModelData.h"
#include "Entity/DesignDataWrapper.h"
#include "Geometry/ModelGeometry.h"


ModelSelectWidget::ModelSelectWidget(QWidget * parent) : BaseDetailActionWidget(parent) {
  models_table_ = NULL;
}

void ModelSelectWidget::Init(std::map<std::string, std::string> parameters) {
  if (models_table_ == NULL) {
    models_table_ = new QTableView(this);
    QRect widget_rect = rect();
    
    models_table_->setGeometry(0,0,widget_rect.width(),widget_rect.height());
  }
  ModelSelectedItemDelegate* item_delegate = new ModelSelectedItemDelegate(this);
  models_table_->setItemDelegate(item_delegate);

  ModelSelectItemModel* item_model = new ModelSelectItemModel(this);
  std::map<std::string, std::string> params;
  std::vector<std::string> model_ids = GetModelIds(params);  
  item_model->set_data(model_ids);
  
  
  models_table_->setModel(item_model);
  int row_num = item_model->rowCount();
  for (int i = 0; i < row_num; i++) {
    models_table_->setRowHeight(i, 98);
  }

  //int horizontal_Offset = models_table_->hor
  int column_num = item_model->columnCount();
  for (int i = 0; i < column_num; i++) {
    models_table_->setColumnWidth(i, 98);
  }

  bool show_grid = models_table_->showGrid();
  models_table_->setShowGrid(false);

  connect(models_table_, SIGNAL(clicked(const QModelIndex &)), this, SLOT(model_selected(const QModelIndex &)));
  
  emit  test_signals();
}

void ModelSelectWidget::model_selected(const QModelIndex &index) {
  int row = index.row();
  QString model_id = index.model()->data(index, Qt::DisplayRole).toString();
  ModelData* model_data = GetModelInfo(model_id.toStdString());
  ModelGeometry* model_geometry = new ModelGeometry(model_data);
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  instance->set_current_selected_geometry(model_geometry);
}

void ModelSelectWidget::test_slots() {
  int a = 0;
}