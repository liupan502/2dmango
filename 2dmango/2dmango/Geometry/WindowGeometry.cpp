#include "WindowGeometry.h"
#include "PenFactory.h"

WindowGeometry::WindowGeometry() :InnerWallGeometry() {
  width_ = 0.0;
  length_ = 0.0;
}

WindowGeometry::WindowGeometry(float width, float length) : InnerWallGeometry(width,length) {
  width_ = width;
  length_ = length;

  QPolygonF path1_polygon = build_path1_polygon();
  path1_ = new PolygonPath(path1_polygon);
  path1_->set_pen(PenFactory::pen1());
  paths_.push_back(path1_);

  QPolygonF path2_polygon = build_path2_polygon();
  path2_ = new PolygonPath(path2_polygon);
  path2_->set_pen(PenFactory::pen1());
  paths_.push_back(path2_);
}

WindowGeometry::~WindowGeometry() {
  if (path1_ != NULL) {
    delete path1_;
    path1_ = NULL;
  }

  if (path2_ != NULL) {
    delete path2_;
    path2_ = NULL;
  }
}

QPolygonF WindowGeometry::build_path1_polygon() {
  QPolygonF polygon;
  qreal half_width = width_ / 2.0;
  QPointF point1(0.0, 0.0);
  polygon << point1;

  QPointF point2(length_, 0.0);
  polygon << point2;

  QPointF point3(length_, half_width);
  polygon << point3;

  QPointF point4(0.0, half_width);
  polygon << point4;
  polygon << point1;
  QPointF offset = position_ - QPointF(length_ / 2.0, width_ / 2.0);
  polygon.translate(offset);
  return polygon;
}

QPolygonF WindowGeometry::build_path2_polygon() {
  QPolygonF polygon;
  qreal half_width = width_ / 2.0;
  QPointF point1(0.0, half_width);
  polygon << point1;

  QPointF point2(length_, half_width);
  polygon << point2;

  QPointF point3(length_, 2*half_width);
  polygon << point3;

  QPointF point4(0.0, 2 * half_width);
  polygon << point4;
  polygon << point1;

  QPointF offset = position_ - QPointF(length_ / 2.0, width_ / 2.0);
  polygon.translate(offset);
  return polygon;
}

void WindowGeometry::update_geometry() {
  QPolygonF path1_polygon = build_path1_polygon();
  path1_->set_polygon(path1_polygon);
  

  QPolygonF path2_polygon = build_path2_polygon();
  path2_->set_polygon(path2_polygon);  
}