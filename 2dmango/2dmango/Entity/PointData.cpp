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
  //point_ = QPointF();
  has_point_data_ = false;
}

bool PointData::has_point_data() {
  return has_point_data_;
}

QJsonObject PointData::ToJson() {
  QJsonObject object;
  QJsonObject parent_object = BaseData::ToJson();
  AttachJsonObject(object, parent_object);
  object.insert("is_generated", QJsonValue(is_generated_));
  object.insert("has_point_data", QJsonValue(has_point_data_));
  QString point_str = PointFToString(point_);
  object.insert("point", QJsonValue(point_str));
  return object;
}

void PointData::InitWithObject(QJsonObject& jsonObject) {
  BaseData::InitWithObject(jsonObject);
  if (jsonObject.contains("is_generated")) {
    is_generated_ = jsonObject["is_generated"].toBool();
  }
  else {
    is_generated_ = false;
  }

  if (jsonObject.contains("has_point_data")) {
    has_point_data_ = jsonObject["has_point_data"].toBool();
  }
  else {
    has_point_data_ = false;
  }

  if (jsonObject.contains("point")) {
    QString point_str = jsonObject["point"].toString();
    point_ = StringToPointF(point_str);
  }
  else {
    point_ = QPointF();
  }
}