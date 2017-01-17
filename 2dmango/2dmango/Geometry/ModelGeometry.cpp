#include "ModelGeometry.h"
#include "Entity/BaseData.h"
#include "Entity/ModelData.h"
#include "Util/LoadFileUtil.h"
#include <QSize>
ModelGeometry::ModelGeometry(ModelData* data) :BaseGeometry(data) {
  //geometry_type_ = GEOMETRY_MODEL;
  img = GetModelImage(data->model_name());
  int a = 0;
}

void ModelGeometry::Draw(QPainter* painter) {
  if (img.isNull()) {
    return;
  }
  painter->save();

  QSize img_size = img.size();
  qreal half_width = data_->width() / 2.0f;
  qreal half_length = data_->length() / 2.0f;
  QPointF offset(half_length, half_width);
  QPointF left_top_point = QPointF(0.0,0.0) - offset; 
  QSize rect_size(half_length *2, half_width *2);
  QRectF target_rectf(left_top_point, rect_size);
  QRect target_rect = target_rectf.toRect();
  QRect img_rect = QRect(0,0,img_size.width(),img_size.height());
  update_transform();
  painter->setTransform(transform_);
  painter->drawImage(target_rect, img, img_rect);
  painter->restore();
}

bool ModelGeometry::IsPointIn(const QPointF& point) {
  QPainterPath path;
  qreal half_width = data_->width() / 2.0f;
  qreal half_length = data_->length() / 2.0f;
  QPointF offset(half_length, half_width);
  //QPointF left_top_point = position() - offset;
  QPointF left_top_point = QPointF(0.0, 0.0) - offset;
  QSize rect_size(half_length * 2, half_width * 2);
  QRectF rect(left_top_point, rect_size);
  path.addRect(rect);
  QTransform invert_transform = transform_.inverted();
  QPointF test_point = invert_transform.map(point);
  return path.contains(test_point);
  //return false;
}