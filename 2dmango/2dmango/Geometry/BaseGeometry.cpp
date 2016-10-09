#include "BaseGeometry.h"
#include <math.h>
BaseGeometry::BaseGeometry() {
  is_visible_ = true;
  index_ = 0;
  transform_ = QTransform();
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


