#include "BaseGeometry.h"
#include "Entity/BaseData.h"
#include <math.h>

BaseGeometry::BaseGeometry(BaseGeometryData* data ) {
  //is_visible_ = true;
  index_ = 0;
  transform_ = QTransform();
  data_ = data;
  geometry_type_ = GEOMETRY_NONE;
  /*if (data != NULL) {
    set_width(data->width());
    set_height(data->height());
    set_length(data->length());

    set_rotation(data->rotation_z());
    set_position(QPointF(data->position().x(), data->position().y()));
  }
  else {
    set_width(0.0);
    set_height(0.0);
    set_length(0.0);

    set_rotation(0.0);
    set_position(QPointF(0.0,0.0));
  }*/
}

void BaseGeometry::Draw(QPainter* painter) {

  if (data_ == NULL ||  !is_visible())
    return;
  /*if (!is_visible_) {
    return;
  }*/
 
  for(int i=0;i<paths_.size();i++){    
    QPen pen = paths_[i]->pen();
    painter->setPen(pen);
    QBrush brush = paths_[i]->brush();
    painter->setBrush(brush);
    
    painter->setTransform(transform_);
    QPainterPath painter_path = paths_[i]->GetPainterPath();
    painter->drawPath(painter_path);
  }

}

void BaseGeometry::set_is_visible(bool is_visible) {
  if (data_ == NULL)
    return;
  data_->set_is_visible(is_visible);
}

bool BaseGeometry::is_visible() {
  return data_== NULL?false:data_->is_visible();
}

bool BaseGeometry::IsPointIn(QPointF point) {
  bool result = false;
  for (int i = 0; i < paths_.size(); i++) {
    QPainterPath path = paths_[i]->GetPainterPath();
    if (path.contains(point)) {
      result = true;
      break;
    }
  }
  return result;
}

void BaseGeometry::MoveTo(QPointF position) { 
  if (data_ == NULL)
    return;
  //position_ = position;
  data_->set_position(QVector3D(position.x(),position.y(),0.0f));
  this->update_geometry();
}

void BaseGeometry::Translate(QPointF offset) {

  if (data_ == NULL) {
    return;
  }
  QVector3D tmp = QVector3D(offset.x(), offset.y(), 0.0);
  data_->set_position(data_->position() + tmp);
  this->update_geometry();
}

void BaseGeometry::update_geometry() {
  update_transform();
}

QRectF BaseGeometry::Rect() {
  return QRectF();
}

void BaseGeometry::update_transform() {
  QTransform transform;  
  transform.translate(position().x(),position().y());
  transform.rotateRadians(rotation());
  transform_ = transform;
}

void BaseGeometry::set_height(float height) {
  if (data_ == NULL) {
    return;
  }
  data_->set_height(height);  
}

void BaseGeometry::set_width(float width) {
  if (data_ == NULL) {
    return;
  }
  data_->set_width(width);
}

void BaseGeometry::set_length(float length) {
  if (data_ == NULL) {
    return;
  }
  data_->set_length(length);  
}

float BaseGeometry::width() {
  return data_==NULL?0.0:data_->width();
}

float BaseGeometry::height() {
  return data_==NULL?0.0:data_->height();
}

float BaseGeometry::length() {
  return data_==NULL?0.0:data_->length();
}

QPointF  BaseGeometry::position() {
  if (data_ == NULL)
    return QPointF();
  QVector3D position = data_->position();
  return QPointF(position.x(),position.y());
}

void BaseGeometry::set_position(QPointF position) {
  if (data_ == NULL)
    return;
  data_->set_position(QVector3D(position.x(), position.y(), 0.0f));
}

void BaseGeometry::set_rotation(float radian) {
  if (data_ == NULL)
    return;
  data_->set_rotation_z(radian);
}

float BaseGeometry::rotation() {
  return data_ == NULL?0.0:data_->rotation_z();
}

GEOMETRY_TYPE BaseGeometry::geometry_type() {
  return geometry_type_;
}

