#include "AuxiliaryLineGeometry.h"

AuxiliaryLineGeometry::AuxiliaryLineGeometry() : BaseGeometry() {
  is_visible_ = false;
}

AuxiliaryLineGeometry::AuxiliaryLineGeometry(QPointF point1, QPointF point2) :BaseGeometry(){
   SetLineGeometry(point1,point2);
   
}

void AuxiliaryLineGeometry::SetLineGeometry(QPointF point1, QPointF point2) {
  point1_ = point1;
  point2_ = point2;
  std::vector<QPointF> points;
  points.push_back(point1);
  points.push_back(point2);
  if (paths_.size() == 0) {    
    LinesPath* lines_path = new LinesPath(points);
    lines_path->set_pen(QPen(Qt::red, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
    paths_.push_back(lines_path);
  }
  else {
    LinesPath* lines_path = (LinesPath*)paths_[0];
    lines_path->set_points(points);
  }
}