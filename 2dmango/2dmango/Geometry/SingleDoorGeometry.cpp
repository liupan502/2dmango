#include "SingleDoorGeometry.h"
#include "PenFactory.h"

SingleDoorGeometry::SingleDoorGeometry() :InnerWallGeometry() {
  width_ = 0.0;
  length_ = 0.0;
}

SingleDoorGeometry::~SingleDoorGeometry(){
  if (path1_ != NULL) {
    delete path1_;
    path1_ = NULL;
  }

  if (path2_ != NULL) {
    delete path2_;
    path2_ = NULL;
  }

  if (contianer_path_ != NULL) {
    delete contianer_path_;
    contianer_path_ = NULL;
  }

  path3_ = NULL;
  path4_ = NULL;
}

SingleDoorGeometry::SingleDoorGeometry(float width, float length) : InnerWallGeometry(width,length) {
  //width_ = width;
  //length_ = length;
  build_geometry(width, length);
}

void SingleDoorGeometry::build_geometry(float width, float length) {
  QPolygonF polygon1 = build_path1_polygon();
  path1_ = new PolygonPath(polygon1);
  path1_->set_pen(PenFactory::pen1());
  //path1_->set_brush(QBrush(Qt::red));
  paths_.push_back(path1_);
  QPolygonF polygon2 = build_path2_polygon();
  path2_ = new PolygonPath(polygon2);
  path2_->set_pen(PenFactory::pen1());
  //path2_->set_brush(QBrush(Qt::red));
  paths_.push_back(path2_);

  contianer_path_ = new ContianerPath();

  std::vector<QPointF> points = build_path4_points();
  path4_ = new LinesPath(points);
  
  contianer_path_->AddSubPath(path4_);


  QRectF rect;
  qreal start_angle, sweep_length;
  QPointF start_point;
  build_path3(rect, start_angle, sweep_length, start_point);

  path3_ = new ArcPath(rect, start_angle, sweep_length, start_point);
  contianer_path_->AddSubPath(path3_);
  contianer_path_->set_pen(PenFactory::pen1());
  //contianer_path_->set_brush(QBrush(Qt::red));
  paths_.push_back(contianer_path_);
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
  polygon << point1;
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
  QPointF point2 = QPointF(path2_width_, width /2.0);
  polygon << point2;
  QPointF point3 = QPointF(path2_width_, width / 2.0 -length);
  polygon << point3;
  QPointF point4 = QPointF(0, width / 2.0 - length);
  polygon << point4; 
  polygon << point1;
  QPointF offset_point = position_ - QPointF(length / 2.0, width / 2.0);
  polygon.translate(offset_point);
  return polygon;
}

void SingleDoorGeometry::build_path3(QRectF& rect, qreal& startAngle, qreal& sweepLength, QPointF& startPoint) {
  QPointF offset = position_ - QPointF(length_ / 2, width_ / 2);
  QPointF top_left_point(2*path2_width_-length_,-(length_-width_/2));
  QPointF bottom_right_point(length_ , length_ - width_ / 2);
  rect = QRectF(top_left_point, bottom_right_point);
  rect.translate(offset);
  startAngle = 0;
  sweepLength = 90;
  startPoint = rect.center() + QPointF(rect.width()/2.0,0.0);
}

void SingleDoorGeometry::update_geometry() {
  QPolygonF polygon1 = build_path1_polygon();
  path1_->set_polygon(polygon1);

  QPolygonF polygon2 = build_path2_polygon();
  path2_->set_polygon(polygon2);

  QRectF rect;
  qreal start_angle, sweep_length;
  QPointF start_point;
  build_path3(rect, start_angle, sweep_length, start_point);
  path3_->Update(rect, start_angle, sweep_length, start_point);

  std::vector<QPointF> points = build_path4_points();
  path4_->set_points(points);
}

std::vector<QPointF> SingleDoorGeometry::build_path4_points() {
  std::vector<QPointF> points;
  QPointF offset = position_ - QPointF(length_ / 2, width_ / 2);
  QPointF point1(path2_width_, -(length_ - width_ / 2));
  points.push_back(point1+offset);

  
  QPointF point2(path2_width_, 0);
  points.push_back(point2 + offset);

  QPointF point3(length_, 0);
  points.push_back(point3 + offset);

  return points;
}
