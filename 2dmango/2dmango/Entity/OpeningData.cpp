#include "OpeningData.h"
#include "Geometry/SingleDoorGeometry.h"
#include "Geometry/DoubleDoorGeometry.h"
#include "Geometry/MoveDoorGeometry.h"
#include "Geometry/WindowGeometry.h"
#include "Geometry/BaseGeometry.h"

OpeningData::OpeningData(std::string name):BaseGeometryData(){
  set_name(name);
}

OpeningData::OpeningData(SingleDoorGeometry geometry,std::string name): BaseGeometryData(){  
  set_name(name);
  opening_type_ = OPENING_SINGLE_DOOR;
  init_geometry(geometry);
}

OpeningData::OpeningData(DoubleDoorGeometry geometry, std::string name) :BaseGeometryData() {
  set_name(name);
  opening_type_ = OPENING_DOUBLE_DOOR;
  init_geometry(geometry);
}

OpeningData::OpeningData(MoveDoorGeometry geometry, std::string name) :BaseGeometryData() {
  set_name(name);
  opening_type_ = OPENING_MOVE_DOOR;
  init_geometry(geometry);
}

OpeningData::OpeningData(WindowGeometry geometry, std::string name) :BaseGeometryData() {
  set_name(name);
  opening_type_ = OPENING_WINDOW;
  init_geometry(geometry);
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