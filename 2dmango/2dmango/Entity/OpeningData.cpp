#include "OpeningData.h"
#include "Geometry/SingleDoorGeometry.h"
#include "Geometry/DoubleDoorGeometry.h"
#include "Geometry/MoveDoorGeometry.h"
#include "Geometry/WindowGeometry.h"
#include "Geometry/BaseGeometry.h"
#include "const.h"

OpeningData::OpeningData(OPENING_TYPE openingType, std::string name ):BaseGeometryData(name){
  set_name(name);
  opening_type_ = openingType;
}

OpeningData::OpeningData(SingleDoorGeometry geometry,std::string name): BaseGeometryData(){  
  set_name(name);
  opening_type_ = OPENING_SINGLE_DOOR;
  init_geometry(geometry);
  set_height(DEFAULT_DOOR_HEIGHT);
  //position_.setZ(50);
}

OpeningData::OpeningData(DoubleDoorGeometry geometry, std::string name) :BaseGeometryData() {
  set_name(name);
  opening_type_ = OPENING_DOUBLE_DOOR;
  init_geometry(geometry);
  set_height(DEFAULT_DOOR_HEIGHT);
}

OpeningData::OpeningData(MoveDoorGeometry geometry, std::string name) :BaseGeometryData() {
  set_name(name);
  opening_type_ = OPENING_MOVE_DOOR;
  init_geometry(geometry);
  set_height(DEFAULT_DOOR_HEIGHT);
}

OpeningData::OpeningData(WindowGeometry geometry, std::string name) :BaseGeometryData() {
  set_name(name);
  opening_type_ = OPENING_WINDOW;
  init_geometry(geometry);
  set_height(DEFAULT_WINDOW_HEIGHT);
  position_.setZ(DEFAULT_WINDOW_Z);
}

BaseGeometry* OpeningData::GetGeometry() {
  BaseGeometry* geometry = NULL;
  switch (opening_type_) {
  case OPENING_SINGLE_DOOR:
    geometry = new SingleDoorGeometry(this);
    break;
  case OPENING_DOUBLE_DOOR:
    geometry = new DoubleDoorGeometry(this);
    break;
  case OPENING_MOVE_DOOR:
    geometry = new MoveDoorGeometry(this);
    break;
  case OPENING_WINDOW:
    geometry = new WindowGeometry(this);
    break;
  default:
    break;
  }
    return geometry;
}

void OpeningData::init_geometry(BaseGeometry geometry) {
  set_width(geometry.width());
  set_height(geometry.height());
  set_length(geometry.length());

  set_position(QVector3D(QVector2D(geometry.position()), 0.0));

  set_rotation_z(geometry.rotation());
}

QJsonObject OpeningData::ToJson() {
  QJsonObject object;
  QJsonObject parent_object = BaseGeometryData::ToJson();
  AttachJsonObject(object, parent_object);
  object.insert("opening_type",QJsonValue((int)(opening_type_)));
  object.insert("wall_name", QJsonValue(wall_name_.c_str()));
  return object;
}

void OpeningData::InitWithObject(QJsonObject& jsonObject) {
  BaseGeometryData::InitWithObject(jsonObject);
  if (jsonObject.contains("opening_type")) {
    opening_type_ = (OPENING_TYPE)jsonObject["opening_type"].toInt();
  }
  else {
    opening_type_ = OPENING_NONE;
  }

  if (jsonObject.contains("wall_name")) {
    wall_name_ = jsonObject["wall_name"].toString().toStdString();
  }
  else {
    wall_name_ = "";
  }
}

OPENING_TYPE OpeningData::type() {
  return opening_type_;
}

