#include "ModelGeometry.h"
#include "Entity/BaseData.h"
#include "Entity/ModelData.h"
#include "Util/LoadFileUtil.h"
#include <QSize>
ModelGeometry::ModelGeometry(ModelData* data) :BaseGeometry(data) {
  geometry_type_ = GEOMETRY_MODEL;
  img = GetModelImage(data->name());
  int a = 0;
}

ModelGeometry::ModelGeometry(std::string modelId) {
  ModelData* tmp_model_data = GetModelInfo(modelId);
  model_name_ = tmp_model_data->model_name();
  set_width(tmp_model_data->width());
  set_height(tmp_model_data->height());
  set_length(tmp_model_data->length());
  
  delete tmp_model_data;
  img = GetModelImage(modelId);
  model_id_ = modelId;
  
}

void ModelGeometry::Draw(QPainter* painter) {
  if (img.isNull()) {
    return;
  }
  painter->save();
  QSize img_size = img.size();
  qreal half_width = img_size.width() / 2.0f;
  qreal half_height = img_size.height() / 2.0f;
  QPointF offset(half_width, half_height);
  QPointF left_top_point = position_ - offset;  
  QRectF target_rectf(left_top_point, img_size);
  QRect target_rect = target_rectf.toRect();
  QRect img_rect = QRect(0,0,img_size.width(),img_size.height());
  painter->drawImage(target_rect, img, img_rect);
  painter->restore();
}