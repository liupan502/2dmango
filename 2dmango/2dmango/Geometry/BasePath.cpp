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