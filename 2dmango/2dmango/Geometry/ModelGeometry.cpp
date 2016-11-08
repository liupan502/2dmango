#include "ModelGeometry.h"
#include "Entity/BaseData.h"
ModelGeometry::ModelGeometry(BaseGeometryData* data) :BaseGeometry(data) {
  geometry_type_ = GEOMETRY_MODEL;
}