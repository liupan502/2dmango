#include "HotRegionGeometry.h"

HotRegionGeometry::HotRegionGeometry(QPointF center, qreal x,qreal y):BaseGeometry(){
  EllipsePath* ellipse_path = new EllipsePath(center,x,y);
  ellipse_path->set_brush(QBrush(QColor(255,123,0,50)));  
  paths_.push_back(ellipse_path);
  is_visible_ = false;
}

HotRegionGeometry::HotRegionGeometry() {
  ;
}

void HotRegionGeometry::MoveTo(QPointF position) {
  ((EllipsePath*)paths_[0])->set_center(position);
}

void HotRegionGeometry::Resize(qreal rx, qreal ry) {
  ((EllipsePath*)paths_[0])->set_rx(rx);
  ((EllipsePath*)paths_[0])->set_ry(ry);
}

bool HotRegionGeometry::ContainsPoint(QPointF point) {
  QPainterPath painter_path = ((EllipsePath*)paths_[0])->GetPainterPath();
  bool result = painter_path.contains(point);
  return result;
}


