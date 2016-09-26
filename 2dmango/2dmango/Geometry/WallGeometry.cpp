#include "WallGeometry.h"
WallGeometry::WallGeometry():BaseGeometry() {
  
}

WallGeometry::WallGeometry(QPolygonF polygon) {
  polygon_ = polygon;
}

WallGeometry::WallGeometry(std::vector<QPointF> points) {
  int size = points.size();
  if(size == 2){
    LinesPath* lines_path = new LinesPath(points);
    lines_path->set_pen(QPen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
    paths_.push_back((BasePath*)lines_path);
  }

  if (size == 6) {
    ;
  }
}