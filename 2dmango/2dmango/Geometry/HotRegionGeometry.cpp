#include "HotRegionGeometry.h"
#include "Entity/BaseData.h"
HotRegionGeometry::HotRegionGeometry(QPointF center, qreal x,qreal y):BaseGeometry(){
  EllipsePath* ellipse_path = new EllipsePath(center,x,y);
  ellipse_path->set_brush(QBrush(QColor(255,123,0,50)));  
  paths_.push_back(ellipse_path);
  //is_visible_ = false;
  data_ = NULL;
  set_is_visible(false);
  
}

HotRegionGeometry::HotRegionGeometry(const HotRegionGeometry& value) {
  if (value.paths_.size() == 1) {
    EllipsePath*  ellipse_path = (EllipsePath*)value.paths_[0];
    QPointF center = ellipse_path->center();
    qreal x = ellipse_path->rx();
    qreal y = ellipse_path->ry();
    EllipsePath* new_ellipse_path = new EllipsePath(center, x, y);
    new_ellipse_path->set_brush(ellipse_path->brush());
    paths_.push_back(ellipse_path);
  }
  
  data_ = new BaseGeometryData();
  set_is_visible(false);
}

HotRegionGeometry::HotRegionGeometry() {
  data_ = new BaseGeometryData();
  set_is_visible(false);
}

HotRegionGeometry::~HotRegionGeometry() {
  if (data_ != NULL) {
    delete data_;
    data_ = NULL;
  }  
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


