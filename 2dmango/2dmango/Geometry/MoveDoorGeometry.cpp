#include "MoveDoorGeometry.h"
#include "PenFactory.h"

MoveDoorGeometry::MoveDoorGeometry() :InnerWallGeometry() {
  width_ = 0.0;
  length_ = 0.0;
}

MoveDoorGeometry::MoveDoorGeometry(float width, float length) : InnerWallGeometry(width,length) {
  //width_ = width;
  //length_ = length;

  QPolygonF path1_polygon = build_path1_polygon();
  path1_ = new PolygonPath(path1_polygon);
  path1_->set_pen(PenFactory::pen1());
  paths_.push_back(path1_);

  QPolygonF path2_polygon = build_path2_polygon();
  path2_ = new PolygonPath(path2_polygon);
  path2_->set_pen(PenFactory::pen1());
  paths_.push_back(path2_);

  QPolygonF path3_polygon = build_path3_polygon();
  path3_ = new PolygonPath(path3_polygon);
  path3_->set_pen(PenFactory::pen1());
  paths_.push_back(path3_);
  
}

QPolygonF MoveDoorGeometry::build_path1_polygon() {
  QPolygonF polygon;
  QPointF point1(0.0, 0.0);
  polygon << point1;

  QPointF point2(0.0, width_);
  polygon << point2;

  QPointF point3(length_, width_);
  polygon << point3;

  QPointF point4(length_, 0.0);
  polygon << point4;
  polygon << point1;


  //QPointF offset = position_ - QPointF(length_/2.0,width_/2.0);
  QPointF offset =  - QPointF(length_ / 2.0, width_ / 2.0);
  polygon.translate(offset);
  return polygon;
}

QPolygonF MoveDoorGeometry::build_path2_polygon() {
  QPolygonF polygon;
  qreal quarter_width = width_ /4.0;
  qreal path_length = length_*0.7;
  QPointF point1(path2_offset, quarter_width);
  polygon << point1;

  QPointF point2(path2_offset+path_length, quarter_width);
  polygon << point2;

  QPointF point3(path2_offset + path_length, 2*quarter_width);
  polygon << point3;

  QPointF point4(path2_offset, 2 * quarter_width);
  polygon << point4;

  polygon << point1;
  //QPointF offset = position_ - QPointF(length_ / 2.0, width_ / 2.0);
  QPointF offset =  - QPointF(length_ / 2.0, width_ / 2.0);
  polygon.translate(offset);
  return polygon;
}

QPolygonF MoveDoorGeometry::build_path3_polygon() {
  QPolygonF polygon;
  qreal quarter_width = width_ /4.0;
  qreal path_length = length_*0.7;
  QPointF point1(length_-path2_offset, 2*quarter_width);
  polygon << point1;

  QPointF point2(length_ - path2_offset - path_length, 2*quarter_width);
  polygon << point2;

  QPointF point3(length_ - path2_offset - path_length, 3 * quarter_width);
  polygon << point3;

  QPointF point4(length_ - path2_offset, 3 * quarter_width);
  polygon << point4;

  polygon << point1;
  //QPointF offset = position_ - QPointF(length_ / 2.0, width_ / 2.0);
  QPointF offset =  - QPointF(length_ / 2.0, width_ / 2.0);
  polygon.translate(offset);
  return polygon;
}

void MoveDoorGeometry::update_geometry() {

  BaseGeometry::update_geometry();
  QPolygonF path1_polygon = build_path1_polygon();
  path1_ ->set_polygon(path1_polygon);  

  QPolygonF path2_polygon = build_path2_polygon();
  path2_->set_polygon(path2_polygon);
 
  QPolygonF path3_polygon = build_path3_polygon();  
  path3_->set_polygon(path3_polygon);
 
}

MoveDoorGeometry::~MoveDoorGeometry() {
  if (path1_ != NULL) {
    delete path1_;
    path1_ = NULL;
  }

  if (path2_ != NULL) {
    delete path2_;
    path2_ = NULL;
  }

  if (path3_ != NULL) {
    delete path3_;
    path3_ = NULL;
  } 
}

