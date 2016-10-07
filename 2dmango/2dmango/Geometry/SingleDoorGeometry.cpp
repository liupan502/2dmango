#include "SingleDoorGeometry.h"

SingleDoorGeometry::SingleDoorGeometry() :BaseGeometry() {
  width_ = 0.0;
  length_ = 0.0;
}

SingleDoorGeometry::SingleDoorGeometry(float width, float length) : BaseGeometry() {
  width_ = width;
  length_ = length;
  build_geometry(width, length);
}

void SingleDoorGeometry::build_geometry(float width, float length) {
  QPolygonF polygon1 = build_path1_polygon();
  path1_ = new PolygonPath(polygon1);
  path1_->set_brush(QBrush(Qt::red));
  paths_.push_back(path1_);
  QPolygonF polygon2 = build_path2_polygon();
  path2_ = new PolygonPath(polygon2);
  path2_->set_brush(QBrush(Qt::red));
  paths_.push_back(path2_);
}

QPolygonF SingleDoorGeometry::build_path1_polygon() {
  float width = width_;
  float length = length_;
  QPolygonF polygon;
  QPointF point1 = QPointF(0.0, 0.0);
  polygon << point1;
  QPointF point2 = QPointF(0.0, width);
  polygon << point2;
  QPointF point3 = QPointF(length, width);
  polygon << point3;
  QPointF point4 = QPointF(length, 0);
  polygon << point4;
  /*PolygonPath* path = new PolygonPath(polygon);
  path->set_brush(QBrush(Qt::red));*/
  QPointF offset_point = position_ - QPointF(length / 2.0, width / 2.0);
  polygon.translate(offset_point);
  return polygon;
}

QPolygonF SingleDoorGeometry::build_path2_polygon() {
  float width = width_;
  float length = length_;
  QPolygonF polygon;
  QPointF point1 = QPointF(0.0, width / 2.0);
  polygon << point1;
  QPointF point2 = QPointF(20, width /2.0);
  polygon << point2;
  QPointF point3 = QPointF(20, width / 2.0 -length);
  polygon << point3;
  QPointF point4 = QPointF(0, width / 2.0 - length);
  polygon << point4;
  /*PolygonPath* path = new PolygonPath(polygon);
  path->set_brush(QBrush(Qt::red));*/
  QPointF offset_point = position_ - QPointF(length / 2.0, width / 2.0);
  polygon.translate(offset_point);
  return polygon;
}

BasePath* SingleDoorGeometry::build_path3(float width, float length) {
  return NULL;
}

void SingleDoorGeometry::update_geometry() {
  QPolygonF polygon1 = build_path1_polygon();
  path1_->set_polygon(polygon1);

  QPolygonF polygon2 = build_path2_polygon();
  path2_->set_polygon(polygon2);
}