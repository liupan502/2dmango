#include "BasePath.h"

QPen BasePath::pen() {
  return pen_;
}

void BasePath::set_pen(QPen pen){
  pen_ = pen;
}

QBrush BasePath::brush(){
  return brush_;
}

void BasePath::set_brush(QBrush brush) {
  brush_ = brush;
}

QPainterPath BasePath::GetPainterPath() {
  return QPainterPath();
}


void BasePath::AddSubPath(BasePath* subPath){
  sub_paths_.push_back(subPath);
}

BasePath::~BasePath(){
  for(int i=0;i<sub_paths_.size();i++){
    if(sub_paths_[i] != NULL){
      delete sub_paths_[i];
      sub_paths_[i] = NULL;
    }  
  }
}

LinesPath::LinesPath(std::vector<QPointF> points){
  points_ = points;
}

void LinesPath::set_points(std::vector<QPointF> points) {
  points_ = points;
}

QPainterPath LinesPath::GetPainterPath(){
  QPainterPath painter_path;
  if (points_.size() < 2) {
    return painter_path;
  }
  painter_path.moveTo(points_[0]);
  for (int i = 1; i < points_.size(); i++) {
    painter_path.lineTo(points_[i]);
  }
  return painter_path;
}


PolygonPath::PolygonPath(QPolygonF polygon){
  polygon_ = polygon;
}

QPainterPath PolygonPath::GetPainterPath() {
  QPainterPath painter_path;
  painter_path.addPolygon(polygon_);
  return painter_path;
}

void PolygonPath::set_polygon(QPolygonF polygon) {
  polygon_ = polygon;
}

EllipsePath::EllipsePath(QPointF center, qreal rx, qreal ry) {
  center_ = center;
  rx_ = rx;
  ry_ = ry;
}

QPainterPath EllipsePath::GetPainterPath(){
  QPainterPath painter_path;
  painter_path.addEllipse(center_,rx_,ry_);
  return painter_path;
}

void EllipsePath::set_center(QPointF center) {
  center_ = center;
}

void EllipsePath::set_rx(qreal rx) {
  rx_ = rx;
}

void EllipsePath::set_ry(qreal ry) {
  ry_ = ry;
}

ArcPath::ArcPath(QRectF rect, qreal startAngle, qreal sweepLength, QPointF start_point) {
  Update(rect, startAngle, sweepLength, start_point);
}

void ArcPath::set_rect(QRectF rect) {
  rect_ = rect;
}

void ArcPath::set_start_angle(qreal startAngle) {
  start_angle_ = startAngle;
}

void ArcPath::set_sweep_length(qreal sweepLength) {
  sweep_length_ = sweepLength;
}

void ArcPath::Update(QRectF rect, qreal startAngle, qreal sweepLength,QPointF start_point) {
  rect_ = rect;
  start_angle_ = startAngle;
  sweep_length_ = sweepLength;
  start_point_ = start_point;
}

QPainterPath ArcPath::GetPainterPath() {
  QPainterPath path;
  path.moveTo(start_point_);
  path.arcTo(rect_,start_angle_,sweep_length_);
  return path;
}

void ContianerPath::AddSubPath(BasePath* subPath) {
  sub_paths_.push_back(subPath);
}

QPainterPath ContianerPath::GetPainterPath() {
  QPainterPath path;
  for (int i = 0; i < sub_paths_.size(); i++) {
    path.addPath(sub_paths_[i]->GetPainterPath());
  }
  return path;
}

ContianerPath::~ContianerPath() {
  for (int i = 0; i < sub_paths_.size(); i++) {
    if (sub_paths_[i] != NULL) {
      delete sub_paths_[i];
      sub_paths_[i] = NULL;
    }
  }
}

