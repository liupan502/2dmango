#include "InnerWallGeometry.h"
#include "Entity/DesignDataWrapper.h"
InnerWallGeometry::InnerWallGeometry() :BaseGeometry() {

}

InnerWallGeometry::InnerWallGeometry(float width, float length):BaseGeometry() {
  width_ = width;
  length_ = length;
}

void InnerWallGeometry::MoveTo(QPointF position) {
  compute_position(position);
  BaseGeometry::MoveTo(position);
}

void InnerWallGeometry::Translate(QPointF offset) {
  QPointF position = position_ + offset;
  compute_position(position);
  BaseGeometry::MoveTo(position);
}

void InnerWallGeometry::compute_position(QPointF& position) {
  DesignDataWrapper* instance = DesignDataWrapper::GetInstance();
  qreal distance;
  WallGeometry wall_geometry = instance->GetClosestWall(position, distance);
  if (distance < 30) {

  }
  else {

  }
}

QRectF InnerWallGeometry::Rect() {
  QRectF rect;
  qreal half_width = width_ / 2.0;
  qreal half_length = length_ / 2.0;
  QPointF top_left_point = position_ - QPointF(half_length, half_width);
  QPointF bottom_right_point = position_ + QPointF(half_length, half_width);
  rect = QRectF(top_left_point, bottom_right_point);
  return rect;
}