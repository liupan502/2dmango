#include "AuxiliaryLineGeometry.h"
#include "Entity/BaseData.h"

AuxiliaryLineGeometry::AuxiliaryLineGeometry() : BaseGeometry() {
  set_is_visible(false);
  data_ = NULL;
}

AuxiliaryLineGeometry::~AuxiliaryLineGeometry() {
  if (data_ != NULL) {
    delete data_;
    data_ = NULL;
  }
 
}

AuxiliaryLineGeometry::AuxiliaryLineGeometry(QPointF point1, QPointF point2) :BaseGeometry(){
   SetLineGeometry(point1,point2);
   data_ = new BaseGeometryData();
}

AuxiliaryLineGeometry::AuxiliaryLineGeometry(const AuxiliaryLineGeometry& value){
  point1_ = value.point1_;
  point2_ = value.point2_;
  SetLineGeometry(point1_, point2_);
  data_ = new BaseGeometryData();
  data_->set_is_visible(value.data_->is_visible());
}

void AuxiliaryLineGeometry::SetLineGeometry(QPointF point1, QPointF point2) {
  //data_ = new BaseGeometryData();
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