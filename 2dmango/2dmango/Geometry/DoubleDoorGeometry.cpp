#include "DoubleDoorGeometry.h"
#include "const.h"
#include "PenFactory.h"
#include "Entity/OpeningData.h"

DoubleDoorGeometry::DoubleDoorGeometry(OpeningData* openingData) :InnerWallGeometry( openingData) {
  /*if (openingData != NULL) {
    width_ = openingData->width();
    length_ = openingData->length();
    //QPointF position = QPointF(openingData->position().x(), openingData->position().y());
    //MoveTo(position);
  }
  else {
    width_ = 0.0;
    length_ = 0.0;
  }


  
  opening_data_ = openingData;*/
  opening_type_ = OPENING_DOUBLE_DOOR;
  build_geometry();
};

/*DoubleDoorGeometry::DoubleDoorGeometry(float width, float length, OpeningData* openingData): InnerWallGeometry(width,length, (BaseGeometryData*)openingData) {
  //width_ = width;
  //length_ = length;

  if (openingData != NULL) {
    width_ = openingData->width();
    length_ = openingData->length();
    //QPointF position = QPointF(openingData->position().x(), openingData->position().y());
    //MoveTo(position);
  }
  

  opening_data_ = openingData;
  opening_type_ = OPENING_DOUBLE_DOOR;
  QPolygonF path1_polygon = build_path1_polygon();
  path1_ = new PolygonPath(path1_polygon);
  path1_->set_pen(PenFactory::pen1());
  paths_.push_back(path1_);

  QPolygonF path2_polygon = build_path2_polygon();
  path2_ = new PolygonPath(path2_polygon);
  path2_->set_pen(PenFactory::pen1());
  paths_.push_back(path2_);

  contianer_path1_ = new ContianerPath();

  std::vector<QPointF> path3_points = build_path3_points();
  path3_ = new LinesPath(path3_points);
  contianer_path1_->AddSubPath(path3_);

  QRectF rect1;
  qreal start_angle1, sweep_length1;
  QPointF start_point1;
  build_path4_params(rect1, start_angle1, sweep_length1, start_point1);
  path4_ = new ArcPath(rect1, start_angle1, sweep_length1, start_point1);
  contianer_path1_->AddSubPath(path4_);
  contianer_path1_->set_pen(PenFactory::pen1());
  paths_.push_back(contianer_path1_);  

  QPolygonF path6_polygon = build_path6_polygon();
  path6_ = new PolygonPath(path6_polygon);
  path6_->set_pen(PenFactory::pen1());
  paths_.push_back(path6_);

  contianer_path2_ = new ContianerPath();

  std::vector<QPointF> path7_points = build_path7_points();
  path7_ = new LinesPath(path7_points);
  contianer_path2_->AddSubPath(path7_);

  QRectF rect2;
  qreal start_angle2, sweep_length2;
  QPointF start_point2;
  build_path8_params(rect2, start_angle2, sweep_length2,start_point2);
  path8_ = new ArcPath(rect2, start_angle2, sweep_length2, start_point2);
  contianer_path2_->AddSubPath(path8_);
  contianer_path2_->set_pen(PenFactory::pen1());
  paths_.push_back(contianer_path2_);

  if (openingData != NULL) {
    QPointF position = QPointF(openingData->position().x(), openingData->position().y());
    MoveTo(position);
  }

}*/

void DoubleDoorGeometry::build_geometry() {
  QPolygonF path1_polygon = build_path1_polygon();
  path1_ = new PolygonPath(path1_polygon);
  path1_->set_pen(PenFactory::pen1());
  paths_.push_back(path1_);

  QPolygonF path2_polygon = build_path2_polygon();
  path2_ = new PolygonPath(path2_polygon);
  path2_->set_pen(PenFactory::pen1());
  paths_.push_back(path2_);

  contianer_path1_ = new ContianerPath();

  std::vector<QPointF> path3_points = build_path3_points();
  path3_ = new LinesPath(path3_points);
  contianer_path1_->AddSubPath(path3_);

  QRectF rect1;
  qreal start_angle1, sweep_length1;
  QPointF start_point1;
  build_path4_params(rect1, start_angle1, sweep_length1, start_point1);
  path4_ = new ArcPath(rect1, start_angle1, sweep_length1, start_point1);
  contianer_path1_->AddSubPath(path4_);
  contianer_path1_->set_pen(PenFactory::pen1());
  paths_.push_back(contianer_path1_);

  QPolygonF path6_polygon = build_path6_polygon();
  path6_ = new PolygonPath(path6_polygon);
  path6_->set_pen(PenFactory::pen1());
  paths_.push_back(path6_);

  contianer_path2_ = new ContianerPath();

  std::vector<QPointF> path7_points = build_path7_points();
  path7_ = new LinesPath(path7_points);
  contianer_path2_->AddSubPath(path7_);

  QRectF rect2;
  qreal start_angle2, sweep_length2;
  QPointF start_point2;
  build_path8_params(rect2, start_angle2, sweep_length2, start_point2);
  path8_ = new ArcPath(rect2, start_angle2, sweep_length2, start_point2);
  contianer_path2_->AddSubPath(path8_);
  contianer_path2_->set_pen(PenFactory::pen1());
  paths_.push_back(contianer_path2_);
}

QPolygonF DoubleDoorGeometry::build_path1_polygon() {
  QPolygonF polygon;
  qreal half_width = width() / 2.0;
  qreal half_length = length() / 2.0;

  QPointF point1(-half_length, 0.0);
  polygon << point1;

  QPointF point2(-half_length, width());
  polygon << point2;

  QPointF point3(half_length, width());
  polygon << point3;

  QPointF point4(half_length, 0.0);
  polygon << point4;

  polygon << point1;
  //QPointF offset = position_ - QPointF(0.0, half_width);
  QPointF offset =  - QPointF(0.0, half_width);
  polygon.translate(offset);
  return polygon;
}

QPolygonF DoubleDoorGeometry::build_path2_polygon() {
  QPolygonF polygon;
  qreal half_width = width() / 2.0;
  qreal half_length = length() / 2.0;

  QPointF point1(-half_length, half_width);
  polygon << point1;

  QPointF point2(-half_length + path2_width_, half_width);
  polygon << point2;

  QPointF point3(-half_length + path2_width_, half_width - half_length);
  polygon << point3;

  QPointF point4(-half_length, half_width - half_length);
  polygon << point4;

  polygon << point1;

  //QPointF offset = position_ - QPointF(0.0, half_width);
  QPointF offset =  - QPointF(0.0, half_width);
  polygon.translate(offset);

  return polygon;
}

std::vector<QPointF> DoubleDoorGeometry::build_path3_points() {
  
  qreal half_width = width() / 2.0;
  qreal half_length = length() / 2.0;
  //QPointF offset = position_ - QPointF(0.0, half_width);
  QPointF offset =  - QPointF(0.0, half_width);
  std::vector<QPointF> points;


  QPointF point3(-half_length + path2_width_, half_width - half_length);
  points.push_back(point3 + offset); 

  QPointF point2(-half_length + path2_width_, 0.0);
  points.push_back(point2 + offset);

  QPointF point1(0.0, 0.0);
  points.push_back(point1 + offset);

  
  return points;
}

void DoubleDoorGeometry::build_path4_params(QRectF& rect, qreal& startAngle, qreal& sweepLength,QPointF& startPoint) {

  qreal half_width = width() / 2.0;
  qreal half_length = length() / 2.0;
  qreal rect_width = 2 * abs(-half_length + path2_width_);
  qreal rect_height = 2 * abs(half_length - half_width);
  QPointF top_left_point(-rect_width,-rect_height/2.0);
  QPointF bottom_right_point(0.0,rect_height/2.0);  
  rect = QRectF(top_left_point, bottom_right_point);
  //QPointF offset = position_ - QPointF(0.0, half_width);
  QPointF offset =  - QPointF(0.0, half_width);
  rect.translate(offset);
  
  startAngle = 0;
  sweepLength = 90;
  startPoint = rect.center() + QPointF(rect.width() / 2.0, 0.0);
}

QPolygonF DoubleDoorGeometry::build_path6_polygon() {
  QPolygonF polygon;
  qreal half_width = width() / 2.0;
  qreal half_length = length() / 2.0;

  QPointF point1(half_length-path2_width_,half_width);
  polygon << point1;

  QPointF point2(half_length, half_width);
  polygon << point2;

  QPointF point3(half_length,half_width-half_length);
  polygon << point3;

  QPointF point4(half_length - path2_width_, half_width - half_length);
  polygon << point4;

  polygon << point1;

  //QPointF offset = position_ - QPointF(0.0, half_width);
  QPointF offset =  - QPointF(0.0, half_width);
  polygon.translate(offset);
  return polygon;
}

std::vector<QPointF> DoubleDoorGeometry::build_path7_points() {

  qreal half_width = width() / 2.0;
  qreal half_length = length() / 2.0;
  std::vector<QPointF> points;
  //QPointF offset = position_ - QPointF(0.0, half_width);
  QPointF offset =  - QPointF(0.0, half_width);
  QPointF point1(0.0, 0.0);
  points.push_back(point1 + offset);

  QPointF point2(half_length - path2_width_,0.0);
  points.push_back(point2 + offset);

  QPointF point3(half_length-path2_width_,half_width-half_length);
  points.push_back(point3 + offset);

  return points;
}

void DoubleDoorGeometry::build_path8_params(QRectF& rect, qreal& startAngle, qreal& sweepLength,QPointF& startPoint) {
  qreal half_width = width() / 2.0;
  qreal half_length = length() / 2.0;

  qreal rect_width = 2 * abs(half_length - path2_width_);
  qreal rect_height = 2 * abs(half_length - half_width);
  QPointF top_left_point(0.0, -rect_height / 2.0);
  QPointF bottom_right_point = top_left_point + QPointF(rect_width, rect_height);
  rect = QRectF(top_left_point, bottom_right_point);
  //QPointF offset = position_ - QPointF(0.0, half_width);
  QPointF offset =  - QPointF(0.0, half_width);
  rect.translate(offset);

  startAngle = 90;
  sweepLength = 90;
  startPoint = rect.center() + QPointF(0.0, -rect.height() / 2.0);

}

void DoubleDoorGeometry::update_geometry() {

  BaseGeometry::update_geometry();

  QPolygonF path1_polygon = build_path1_polygon();
  path1_->set_polygon(path1_polygon);

  QPolygonF path2_polygon = build_path2_polygon();
  path2_->set_polygon(path2_polygon);
  
  std::vector<QPointF> path3_points = build_path3_points();
  path3_->set_points(path3_points);  

  QRectF rect1;
  qreal start_angle1, sweep_length1;
  QPointF start_point1;
  build_path4_params(rect1, start_angle1, sweep_length1,start_point1);
  path4_->Update(rect1, start_angle1, sweep_length1,start_point1);  

  QPolygonF path6_polygon = build_path6_polygon();
  path6_->set_polygon(path6_polygon);

  std::vector<QPointF> path7_points = build_path7_points();
  path7_->set_points(path7_points); 

  QRectF rect2;
  qreal start_angle2, sweep_length2;
  QPointF start_point2;
  build_path8_params(rect2, start_angle2, sweep_length2, start_point2);
  path8_->Update(rect2, start_angle2, sweep_length2, start_point2);
}

DoubleDoorGeometry::~DoubleDoorGeometry() {
  if (path1_ != NULL) {
    delete path1_;
    path1_ = NULL;
  }

  if (path2_ != NULL) {
    delete path2_;
    path2_ = NULL;
  }

  if (contianer_path1_ != NULL) {
    delete contianer_path1_;
    contianer_path1_ = NULL;
  }

  path3_ = NULL;
  path4_ = NULL;

  if (path6_ != NULL) {
    delete path6_;
    path6_ = NULL;
  }

  if (contianer_path2_ != NULL) {
    delete contianer_path2_;
    contianer_path2_ = NULL;
  }

  path7_ = NULL;
  path8_ = NULL;
}