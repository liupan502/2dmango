#include "PointData.h"

PointData::PointData() :BaseData() {
  has_point_data_ = false;
}

PointData::PointData(std::string name, QPointF point) : BaseData(name) {
  point_ = point;
  has_point_data_ = true;
}

void PointData::set_point(QPointF point) {
  point_ = point;
  has_point_data_ = true;
}

QPointF PointData::point() {
  return point_;
}

void PointData::Reset() {
  point_ = QPointF();
  has_point_data_ = false;
}

bool PointData::has_point_data() {
  return has_point_data_;
}
std::string PointData::ToJson() {
  return "";
}