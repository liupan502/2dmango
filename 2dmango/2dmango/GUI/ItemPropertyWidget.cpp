#include "ItemPropertyWidget.h"

void ItemPropertyWidget::SetGetmetryData(BaseGeometryData* data) {
  if (detail_widget_ != NULL) {
    detail_widget_->set_data(data);
  }
}

void OpeningPropertyDetailWidget::set_data(BaseGeometryData* data) {
  if (data_->geometry_type() != GEOMETRY_OPENING)
    return;
  data_ = data;
}

void OpeningPropertyDetailWidget::UpdateContent(bool isViewToData) {

}

void ModelPropertyDetailWidget::set_data(BaseGeometryData* data) {
  if (data->geometry_type() != GEOMETRY_MODEL)
    return;
  data_ = data;
}

void ModelPropertyDetailWidget::UpdateContent(bool isViewToData) {

}

