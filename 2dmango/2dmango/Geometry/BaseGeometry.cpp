#include "BaseGeometry.h"
#include <math.h>
BaseGeometry::BaseGeometry(BaseGeometryData* data ) {
  is_visible_ = true;
  index_ = 0;
  transform_ = QTransform();
  data_ = data;
  geometry_type_ = GEOMETRY_NONE;
}

void BaseGeometry::Draw(QPainter* painter) {
  if (!is_visible_) {
    return;
  }
 
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
  is_visible_ = is_visible;
}

bool BaseGeometry::is_visible() {
  return is_visible_;
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
  position_ = position;
  this->update_geometry();
}

void BaseGeometry::Translate(QPointF offset) {  
  position_ += offset;
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
  transform.translate(position_.x(),position_.y());
  transform.rotateRadians(rotate_radian_);
  transform_ = transform;
}

void BaseGeometry::set_height(float height) {
  height_ = height;
}

void BaseGeometry::set_width(float width) {
  width_ = width;
}

void BaseGeometry::set_length(float length) {
  length_ = length;
}

float BaseGeometry::width() {
  return width_;
}

float BaseGeometry::height() {
  return height_;
}

float BaseGeometry::length() {
  return length_;
}

QPointF  BaseGeometry::position() {
  return position_;
}

void BaseGeometry::set_position(QPointF position) {
  position_ = position;
}

void BaseGeometry::set_rotation(float radian) {
  rotate_radian_ = radian;
}

float BaseGeometry::rotation() {
  return rotate_radian_;
}

GEOMETRY_TYPE BaseGeometry::geometry_type() {
  return geometry_type_;
}

